#include "dh.h"

/*	Smooth.c
	a 9-point Savisky-Gavoy smoothing routine
	from the fortran source in the original paper
*/

int smooth_sg(float *array, int arraysize)
{
	
    float *tempbuffer, total;
	int i;
	
	tempbuffer = (float *)malloc(arraysize * sizeof(float));
	
	if (tempbuffer == NULL) {
		perror("out of memory - malloc failed");
		exit(1);
	}

	/* smoothing loop */

    for (i=0; i<arraysize; i++) {
        
        total = 0.;
		
		if (i < 9 || (arraysize -i) < 9)
			
			tempbuffer[i] = array[i];
		
		else {
			
			total = 59* array[i] + 54*(array[i-1]+array[i+1]) + 39*(array[i-2] + array[i+2]) + 14*(array[i-3] + array[i+3]) - 
			21*(array[i-4] + array[i+4]);
			
			tempbuffer[i] = total/231;
		}
	}
            
 
			
	for (i=0; i< arraysize; i++) /* fill array with smoothed values */
		array[i] = tempbuffer[i];
    
	free(tempbuffer);

	return 0;	

}
/*  
*	boxcar smoothing of 1D array
*/  

int boxcar_smooth(float *array, int arraysize, int boxcarsize)
{
	float *tempbuffer, total;
	int i, j;
	
	tempbuffer = (float *)malloc(arraysize * sizeof(float));
	
	if (tempbuffer == NULL) {
		perror("out of memory - malloc failed");
		exit(1);
	}
	
	/*  fill temp array with smoothed values  */
	for (i=0; i<arraysize; i++) {
		
		if (i < boxcarsize || (arraysize -i) < boxcarsize)
			
			tempbuffer[i] = array[i];
		
		else {
			total = 0.;
			
			for(j=0; j<boxcarsize; j++) 
				total += array[ i + (j-boxcarsize/2)];
			
			tempbuffer[i] = total/boxcarsize;
		}
	}
	
	/*  fill contents of array with smoothed values */
	
	for (i=0; i< arraysize; i++)
		array[i] = tempbuffer[i];
		
	free(tempbuffer);
	
	return 0;
}

