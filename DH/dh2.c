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

#define PERCENT 5
#define REFD = -135
#define REFO = -16.9
#define SAMPLERATE  1        /*hz*/
#define D_HIGH_THRESHOLD 60.0
#define D_LOW_THRESHOLD 0.1
#define H_HIGH_THRESHOLD 30000
#define H_LOW_THRESHOLD 50
#define PEAKSKIRT 20  /* peak skirt - how much of the peak to grab beyond the threshold - must be even */
#define MEMORY 0 /* Memory effect - chop out first x samples because of memory effect */
/* default integration threshold */


int main(int argc, char *argv[])
{
	
    int threshold = THRESHOLD, smooth = FALSE, c, peakno=0, cntr=0, j, i=0, foundpeak = FALSE, memory=MEMORY;
    int boxcar = 5, k=0, peakstart, peakend, ref=FALSE, liq_water = FALSE, smoothmethod =0 ;
    float peak_array_d[10000], peak_array_18o[10000], peak_array_h2o[10000], h2osum = 0.0;
    float dh, o18o16, deltaD, delta18o, percent = 0.0, dref = 0.0, oref = 0.0;
    float dexcess, dh_ref = 0.000382, o18o16_ref = 0.002030;  /* give refs reasonable ref values */
    float temp = 25.0, alphaD = 1.0, alphaO=1.0;
    char *inputfile = NULL;

   while (( c=getopt(argc, argv, "b:f:t:p:d:o:s:rwT:hm:")) != -1)
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

			case 'w':
				liq_water = TRUE;
				break;	
			case 'T':
				temp = atof(optarg) + 273.0;
				break;
            case 'm':
                memory=atoi(optarg)/SAMPLERATE;
                break;
			case 'h':
				help();
                exit(0);
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
	
	remove_d_noise(d, mainarraysize, D_LOW_THRESHOLD, D_HIGH_THRESHOLD);
	remove_d_noise(h2o, mainarraysize, H_LOW_THRESHOLD, H_HIGH_THRESHOLD);

	if (liq_water == TRUE) {    /*( calculate alpha values */
		alphaD = get_alpha_h(temp);
		alphaO = get_alpha_o(temp);
         }
    
	/* dumparray(d, mainarraysize); */

	printf("#****************************************\n");
	printf("#      PROGRAM:  %s\n", argv[0]);
	printf("#      FILE: %s*\n", inputfile);
	printf("#****************************************\n");
	printf("# Threshold = %d\n", threshold);
	printf("# baseline = %f percent\n", percent);
	if (ref == TRUE) {
		printf("# DeltaD reference =  %f   ", dref);
		printf("# Delta18O reference =  %f\n", oref);
	}
	if (smooth == TRUE) {
		printf("# Smoothing on\n");
        if (smoothmethod == 1) printf("#  smoothing by 9-point cubic spline\n");
        else  printf("# boxcar size = %d\n", boxcar);
	}
	if (liq_water == TRUE) {
	    printf("# values reported as water in equilibrium with vapour, temp = %5.2fC\n", temp-273.0);
	    printf("# alpha D = %f       alpha O = %f\n", alphaD, alphaO);
	 }
	printf("#\n#\n#Peak  time(s)  samples    size	   D/H	     18O/16O	  DeltaD    Delta18O\n");
	printf("#------------------------------------------------------------------------------\n");

	
    for (i = 0; i < mainarraysize; i++) {
        
        if (h2o[i] > threshold) {  /*found a peak */
            foundpeak = TRUE; 
	    peakstart = i;
            while (h2o[peakstart + k] > threshold) k++;
	    peakend = peakstart+k; 
	    
	    k=0; /* reset k */
	    
	    for (cntr = 0; cntr < (peakend - peakstart + PEAKSKIRT); cntr++) {
	    	peak_array_h2o[cntr]=h2o[peakstart + memory + cntr -(PEAKSKIRT/2)];
            	peak_array_18o[cntr]=o18[peakstart + memory + cntr -(PEAKSKIRT/2)];  /*fill up peak arrays */
		/*dexcess = 2.28e-10*h2o[peakstart+ cntr]*h2o[peakstart + cntr];*/
		dexcess = 0.00005*h2o[peakstart+ cntr-(PEAKSKIRT/2)];
            peak_array_d[cntr] = d[peakstart + memory + cntr-(PEAKSKIRT/2)]+ dexcess; /*0001*h2o[peakstart -10 + cntr];*/
	    }
	    i=peakend;
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
	    
	    h2osum = trapz(peak_array_h2o, cntr, percent);
            dh = trapz(peak_array_d, cntr, percent) /h2osum;
	    o18o16 = trapz(peak_array_18o, cntr, percent) / h2osum;	    

 /*           h2osum = getsum(peak_array_h2o, cntr, percent);
            dh = getsum(peak_array_d, cntr, percent) /h2osum;
	    o18o16 = getsum(peak_array_18o, cntr, percent) / h2osum;
*/

/*	    if (liq_water == TRUE && peakno != 1) {
		dh = get_dh_w(dh, temp);  calculate liquid water in eq 
		o18o16 = get_1816_w(o18o16, temp);
	    }

*/            

	    if (ref == TRUE && peakno == 1 ) { /* big peak - its the ref */
                dh_ref = dh;
                o18o16_ref = o18o16;         
            } 
            
            /* Otherwise its a sample, but should calculate delta value of sample vs ref anyway */
            
            deltaD = ((dh/dh_ref)-1.0)*1000 + dref;
            delta18o = ((o18o16/o18o16_ref)-1.0)*1000 + oref;

	    if (liq_water == TRUE && peakno != 1) {

		deltaD = (alphaD * (1000 + deltaD))-1000;
		delta18o = (alphaO * (1000 + delta18o))-1000;
            }

            printf("%6d %6d %6d %10.2e %10f %10f %10.1f %10.2f\n",
                   peakno, peakstart/SAMPLERATE, cntr, h2osum, dh, o18o16, deltaD, delta18o); /* correction factors on dD, 18O epirically calculated for LG */

	    /* set peak arrays to 0 */
            for (j = 0; j<10000; j++) {
		    peak_array_h2o[j]= 0;
	            peak_array_18o[j]= 0;
		    peak_array_d[j] = 0;
	    }
		
            foundpeak = FALSE;
            
          } 
            else {/*do nothing*/}
            
        
                                 
        
    }
    
   	printf("#------------------------------------------------------------------------------\n");
	
	return 0;	
}
