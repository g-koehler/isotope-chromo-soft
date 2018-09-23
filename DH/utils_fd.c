/*  	various utility functions  
	G.  Koehler
	SART observatory 
	Feb 2001
	
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define PI 	3.141592

/*  mkgauss - returns the point on a gaussian curve of with a sigma and mu of
    sigma and mu.  scale is the scaling factor
*/


float mkgauss (float x, float scale, float sigma, float mu)
{
	float result;
	result = (exp((-1.0*((x-mu) * (x-mu))) / (2.0 * (sigma * sigma))) /
	(sigma *
	sqrt(2*PI)));
	
	return scale * result;
	
	
	
}


/*  finds the minimum value in the passed 1D array */

float min(float *array, int arraysize)
{
	float minimum = 0.;
	int i;
	
	minimum = *array; /* set minumum to first element in array */
	
	for (i=0; i<arraysize; i++) {
		if (array[i] < minimum) 
			minimum = array[i];
	}
	
	return minimum;
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
			
/*  gaussarea - get 2sigma area under normal peak of width sigma with 
*   center height of x
*/

float gaussarea(float x, float sigma)
{
	int i;
	float total= 0.0, tempsum = 0.0;
	
	for (i = -(int)sigma; i < (int)sigma; i++) {
	
		
		tempsum = mkgauss(0.0, x, sigma, (float)i);
		total += tempsum * tempsum;
	}
	
	return total;
}  
	
	
/*  Random number routine from numerical recipies */


float ran0(idum)
int *idum;
{
	static float y,maxran,v[98];
	float dum;
	static int iff=0;
	int j;
	unsigned i;

	if (*idum < 0 || iff == 0) {
		iff=1;
		i=2;
		maxran=RAND_MAX + 1.0;
		
		srand(*idum);
		*idum=1;
		for (j=1;j<=97;j++) dum=rand();
		for (j=1;j<=97;j++) v[j]=rand();
		y=rand();
	}
	j=1+97.0*y/maxran;
	
	y=v[j];
	v[j]=rand();
	return y/maxran;
}

/*  baseline normalize 1D array   */

int baseline_norm(float *array, int arraysize)
{
	float minimum;
	int i;
	
	
	/*  get minimum value from array  */
	
	minimum = min(array, arraysize);
	
	
	
	/*  fill contents of array with normalized values values */
	
	for (i=0; i< arraysize; i++)
		array[i] = array[i] - minimum;
		
	return 0; /*success */
}
		
/*  get sum of bins around point i in array  */

float getsum(float *array, int arraysize, int i, int boxcarsize)
{
	float total = 0.0;
	int j;
	
	
	
	if (i < boxcarsize/2 )  /* check to see if in bounds of array */
			
		i = boxcarsize/2;
			
	if ((arraysize -i) < boxcarsize/2)
			
		i = arraysize - boxcarsize/2;
		
			
	for(j=0; j<boxcarsize; j++) /* total bins in boxcar */
			
		total += array[ i + (j-boxcarsize/2)];
			
			
	
	return total;
}


float getave( float *array, int arraysize)
{
	float sum = 0.0;
	int i;
	
	for (i = 0; i < arraysize; i++) {
		sum += array[i];
	}
	
	return sum / (float) arraysize;
}

