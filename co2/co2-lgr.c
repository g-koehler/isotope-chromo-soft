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

#include "co2.h"  

#define PERCENT 1
#define REFC = 0
#define REFO = 0
#define SAMPLERATE  1       /*hz*/
#define SMOOTHMETHOD  0      /* 0 - boxcar smoothing  1-savistsky-golay */
#define MAJOR  500000000
#define MINOR1 50000000000
#define MINOR2 10000000000

/* default integration threshold */


int main(int argc, char *argv[])
{
	
    int threshold = THRESHOLD, smooth = FALSE, c, peakno=0, cntr=0, j, i=0, foundpeak = FALSE;

    int boxcar = 5, k=0, peakstart, peakend, ref=FALSE, smoothmethod = SMOOTHMETHOD;

    int craig = TRUE;  /* 17O correction - not exactly craig but easier to remember */

    float peak_array_44[10000], peak_array_45[10000], peak_array_46[10000], sum = 0.0;

    float c13c12, o18o16, delta13c, delta18o, percent = PERCENT, cref = 0.0, oref = 0.0;

    float c13c12_ref = 1.18372, o18o16_ref = 1.384157;  /* give refs reasonable ref values */

    char *inputfile = NULL;

   while (( c=getopt(argc, argv, "cb:f:t:p:d:o:s:r")) != -1)
		switch (c) {
			case 't':
				threshold = atoi(optarg);				
				break;

			case 'p':
				percent = atof(optarg);				
				break;

			case 'd':
				cref = atof(optarg);				
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

			case 'c':
				craig = FALSE;
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
	if (ref==TRUE) {
		printf("# Delta13C reference =  %f   ", cref);
		printf("# Delta18O reference =  %f\n", oref);
	}

	if (smooth == TRUE) {
		printf("# Smoothing on\n");
        	if (smoothmethod == 1) printf("# smoothing by 9-point cubic spline\n");
        	else  printf("# boxcar size = %d\n", boxcar);
	}

	if (craig == TRUE) printf ("# 17O corrected for CO2\n");

	printf("#\n#\n#Peak  time(s)  samples    size	   13C/12C   18O/16O	  Delta13C    Delta18O\n");
	printf("#------------------------------------------------------------------------------\n");

	
    for (i = 0; i < mainarraysize; i++) {
        
        if (mass44[i] > threshold) {  /*found a peak */
            foundpeak = TRUE; 
	    peakstart = i;
            while (mass44[peakstart + k] > threshold) k++;
	    peakend = peakstart+k; 
	    
	    k=0; /* reset k */
	    
	    for (cntr = 0; cntr < (peakend - peakstart) + 10; cntr++) {
	    	peak_array_44[cntr]=mass44[peakstart -5 + cntr];
            	peak_array_45[cntr]=mass45[peakstart -5 + cntr];  /*fill up peak arrays */
            	peak_array_46[cntr] = mass46[peakstart -5 + cntr]; 
	    }
	    i=peakend;
        }   
            
        
        else if (foundpeak == TRUE) {
            peakno++;

	    if (smooth == TRUE) {
            if (smoothmethod == 1) {
                smooth_sg(peak_array_44, cntr);
                smooth_sg(peak_array_45, cntr);
                smooth_sg(peak_array_46, cntr);
            }
            else {    
                
                boxcar_smooth(peak_array_44, cntr, boxcar);
                boxcar_smooth(peak_array_45, cntr, boxcar);
                boxcar_smooth(peak_array_46, cntr, boxcar);
            }
	    }
	    
	    sum = simpz(peak_array_44, cntr, percent);
            c13c12 = simpz(peak_array_45, cntr, percent) /sum;
	    o18o16 = simpz(peak_array_46, cntr, percent) / sum;	    

 /*           h2osum = getsum(peak_array_h2o, cntr, percent);
            dh = getsum(peak_array_d, cntr, percent) /h2osum;
	    o18o16 = getsum(peak_array_18o, cntr, percent) / h2osum;
*/

            

	    if (ref == TRUE && peakno == 1 ) { /* big peak - its the ref */
                c13c12_ref = c13c12;
                o18o16_ref = o18o16;         
            } 
            
            /* Otherwise its a sample, but should calculate delta value of sample vs ref anyway */
            
            delta13c = ((c13c12/c13c12_ref)-1.0)*1000;
            delta18o = ((o18o16/o18o16_ref)-1.0)*1000;

            if (craig == TRUE) {
                delta13c = o17_corr(delta13c, delta18o);
                delta18o = craig_o(delta18o, delta13c);
            }
            
            printf("%6d %6d %6d %10.2e %10f %10f %10.2f %10.2f\n",
                   peakno, peakstart/SAMPLERATE, cntr, sum, c13c12, 
		   o18o16, delta13c + cref, delta18o + oref);

	    /* set peak arrays to 0 */
            for (j = 0; j<10000; j++) {
		    peak_array_44[j]= 0;
	            peak_array_45[j]= 0;
		    peak_array_46[j] = 0;
	    }
		
            foundpeak = FALSE;
            
          } 
            else {/*do nothing*/}
            
        
                                 
        
    }
    
   	printf("#------------------------------------------------------------------------------\n");
	
	return 0;	
}
