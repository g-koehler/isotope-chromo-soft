/*	LGR data processor that finds peaks in water 
      	integrates the peaks and spits out the data -	input is a simplified LGR data file 		
	recuded with the shellscript "peak_reduce"
	Arguments are the input file name and threshold value
	outputs to stdout
	A workable C program from the perl script
	G. Koehler 2011
*/


#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <math.h>
#include <getopt.h>

#include "dh.h"  

#define PERCENT 10
#define REFD = -135
#define REFO = -16.9
#define SAMPLERATE  2        /*hz*/

/* default integration threshold */


int main(int argc, char *argv[])
{
	
    int threshold = THRESHOLD, smooth = FALSE, c, peakno=0, cntr=0, j, i=0, foundpeak = FALSE;
    int boxcar = 5,ref=FALSE, smoothmethod =0;
    float peak_array_d[1000], peak_array_18o[1000], peak_array_h2o[1000], h2osum = 0.0;
    float dh, o18o16, deltaD, delta18o, percent = 0.0, dref = 0.0, oref = 0.0;
    float dh_ref = 0.000282, o18o16_ref = 0.001982;  /* give refs reasonable ref values */
    char *inputfile = NULL;

   while (( c=getopt(argc, argv, "b:f:t:p:d:o:s:r")) != -1)
		switch (c) {
			case 't':
				threshold = atoi(optarg);
				break;

			case 'p':
				percent = atof(optarg);
				break;

			case 'd':
				dref = atof(optarg);
				break;
			case 'o':
				oref = atof(optarg);
				break;

			case 's':
				smooth = TRUE;
				smoothmethod = atoi(optarg);
				break;

			case 'b':
				boxcar = atoi(optarg);
				break;

			case 'f':
				inputfile = optarg;
				
				break;

			case 'r':
				ref = TRUE;
				break;
					
			default:
				break;
		}
/*
    if (argc < 3)
        percent = PERCENT;
    else
        percent = atof(argv[2]);
*/	
    if (readfile(inputfile) != 0){ /*read the filename */
    		fprintf(stderr, "main:  unable to read input file\n");
		exit(-1);
	}		
	
    
	/* dumparray(d, mainarraysize); */

	printf("#****************************************\n");
	printf("#      PROGRAM:  %s\n", argv[0]);
	printf("#      FILE: %s*\n", inputfile);
	printf("#****************************************\n");
	printf("# Threshold = %d\n", threshold);
	printf("# baseline = %f percent\n", percent);
	printf("# DeltaD reference =  %f   ", dref);
	printf("# Delta18O reference =  %f\n", oref);
    if (smooth == TRUE) {
		    printf("# Smoothing on\n");
		    printf("# boxcar size = %d\n", boxcar);
	 }
	
	    
	
	
	printf("#\n#\n#Peak      size	   D/H	     18O/16O	  DeltaD    Delta18O\n");
	printf("#-------------------------------------------------------------------------\n");


	
    while (i<mainarraysize) {
        
        if (h2o[i] > threshold) {  /*found a peak */
            foundpeak = TRUE;
            peak_array_h2o[cntr]=h2o[i];
            peak_array_18o[cntr]=o18[i];  /*fill up peak arrays */
            peak_array_d[cntr] = d[i];
            cntr++;
            i++;
            
        }
        else if (foundpeak == TRUE) {
            peakno++;

	    if (smooth == TRUE) {
            if (smoothmethod == 1) {
                smooth_sg(peak_array_h2o, cntr);
                smooth_sg(peak_array_18o, cntr);
                smooth_sg(peak_array_d, cntr);   
                
            }
            else {
                boxcar_smooth(peak_array_h2o, cntr,boxcar);
                boxcar_smooth(peak_array_18o, cntr,boxcar);
                boxcar_smooth(peak_array_d, cntr,boxcar);
            }

	    }
            h2osum = simpz(peak_array_h2o, cntr, percent);
            dh = (simpz(peak_array_d, cntr, percent) + (0.0001*h2osum)) /h2osum;
            o18o16 = simpz(peak_array_18o, cntr, percent) / h2osum;

	    if (ref == TRUE && peakno == 1 ) { /* check for ref flag - its the first peak */
                dh_ref = dh;
                o18o16_ref = o18o16;         
            } 
            
            /* Otherwise its a sample, but should calculate delta value of sample vs ref anyway */
            
            deltaD = ((dh/dh_ref)-1.0)*1000 + dref;
            delta18o = ((o18o16/o18o16_ref)-1.0)*1000 + oref;
            
            printf("%6d  %10.2e %10f %10f %10.1f %10.2f\n",
                   peakno, h2osum, dh, o18o16, deltaD, delta18o);

	    /* set peak arrays to 0 */
            for (j = 0; j<1000; j++) {
		    peak_array_h2o[j]= 0;
	            peak_array_18o[j]= 0;
		    peak_array_d[j] = 0;
	    }
		
            foundpeak = FALSE;
            cntr = 0;
          } 
            else i++;
            
        
                                 
        
    }
    
    	
	printf("#-------------------------------------------------------------------------\n");
	return 0;	
}
