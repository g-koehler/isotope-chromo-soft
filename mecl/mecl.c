/*	LGR data processor that finds peaks in water 
      	integrates the peaks and spits out the data -	input is a simplified LGR data file 		
	recuded with the shellscript "peak_reduce"
	Arguments are the input file name and threshold value
	outputs to stdout
	A workable C program from the perl script
	G. Koehler 2011
	modified for mecl Oct 2011
*/


#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <math.h>
#include <getopt.h>

#include "mecl.h"  

#define PERCENT 1
#define REFC = 0
#define REFO = 0
#define SAMPLERATE  10       /*hz*/
#define SMOOTHMETHOD  0      /* 0 - boxcar smoothing  1-savistsky-golay */
#define MAJOR  500000000
#define MINOR1 50000000000
#define MINOR2 10000000000

/* default integration threshold */


int main(int argc, char *argv[])
{
	
    int smooth = FALSE, c, peakno=0, cntr=0, j, i=0, foundpeak = FALSE;

    int boxcar = 5, k=0, peakstart, peakend, ref=FALSE, smoothmethod = SMOOTHMETHOD;

    float peak_array_major[10000], peak_array_minor[10000], sum = 0.0;

    float c13c12, delta13c, percent = PERCENT, cref = 0.0, threshold = THRESHOLD ;

    float c13c12_ref = 1.18372; /* give refs reasonable ref values */

    char *inputfile = NULL;

   while (( c=getopt(argc, argv, "b:f:t:p:d:s:r")) != -1)
		switch (c) {
			case 't':
				threshold = atof(optarg);				
				break;

			case 'p':
				percent = atof(optarg);				
				break;

			case 'd':
				cref = atof(optarg);				
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
	printf("# Threshold = %f\n", threshold);
	printf("# baseline = %f percent\n", percent);
	if (ref==TRUE) {
		printf("# Delta37Cl reference =  %f   ", cref);
		
	}

	if (smooth == TRUE) {
		printf("# Smoothing on\n");
        	if (smoothmethod == 1) printf("# smoothing by 9-point cubic spline\n");
        	else  printf("# boxcar size = %d\n", boxcar);
	}


	printf("#\n#\n#Peak  time(s)  samples    size	   37Cl/35Cl   Delta37Cl    \n");
	printf("#------------------------------------------------------------------\n");

	
    for (i = 0; i < mainarraysize; i++) {
        
        if (major[i] > threshold) {  /*found a peak */
            foundpeak = TRUE; 
	    peakstart = i;
            while (major[peakstart + k] > threshold) k++;
	    peakend = peakstart+k; 
	    
	    k=0; /* reset k */
	    
	    for (cntr = 0; cntr < (peakend - peakstart) +300 ; cntr++) {
	    	peak_array_major[cntr]=major[peakstart -20 + cntr];
            	peak_array_minor[cntr]=minor[peakstart -20 + cntr];  /*fill up peak arrays */
         
	    }
	    i=peakend;
        }   
            
        
        else if (foundpeak == TRUE) {
            peakno++;

	    if (smooth == TRUE) {
            if (smoothmethod == 1) {
                smooth_sg(peak_array_major, cntr);
                smooth_sg(peak_array_minor, cntr);
               
            }
            else {    
                
                boxcar_smooth(peak_array_major, cntr, boxcar);
                boxcar_smooth(peak_array_minor, cntr, boxcar);
            
            }
	    }
	    
	    sum = simpz(peak_array_major, cntr, percent);
            c13c12 = simpz(peak_array_minor, cntr, percent) /sum;
	    

 /*           h2osum = getsum(peak_array_h2o, cntr, percent);
            dh = getsum(peak_array_d, cntr, percent) /h2osum;
	    o18o16 = getsum(peak_array_18o, cntr, percent) / h2osum;
*/

            

	    if (ref == TRUE && peakno == 1 ) { /* big peak - its the ref */
                c13c12_ref = c13c12;
               
            } 
            
            /* Otherwise its a sample, but should calculate delta value of sample vs ref anyway */
            
            delta13c = ((c13c12/c13c12_ref)-1.0)*1000;
           

         
            
            printf("%6d %6d %6d %10.2e %10f %10.2f \n",
                   peakno, peakstart/SAMPLERATE, cntr, sum, c13c12, 
		   delta13c + cref);

	    /* set peak arrays to 0 */
            for (j = 0; j<10000; j++) {
		    peak_array_major[j]= 0;
	            peak_array_minor[j]= 0;
		   
	    }
		
            foundpeak = FALSE;
            
          } 
            else {/*do nothing*/}
            
        
                                 
        
    }
    
   	printf("#------------------------------------------------------------------------------\n");
	
	return 0;	
}
