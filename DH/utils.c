/*  	various utility functions  
	G.  Koehler
	
	Apr 2011
	
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* #include "dh.h" */


#define PI 	3.141592


/*  finds the minimum value in the passed 1D array */

float array_max(float *array, int arraysize)
{
	float maximum = 0.;
	int i;
	
	maximum = *array; /* set maximum to first element in array */
	
	for (i=0; i<arraysize; i++) {
		if (array[i] > maximum) 
			maximum = array[i];
	}
	
	return maximum;
}



			
/*  baseline normalize 1D array   */

int baseline_norm(float *array, int arraysize, float percent)
{
	float maximum;
	int i;
	
	
	/*  get minimum value from array  */
	
	maximum = array_max(array, arraysize);
	
	
	
	/*  fill contents of array with normalized values values */
	
	for (i=0; i< arraysize; i++)
		array[i] = array[i] - maximum * percent/100;
		
	return 0; /*success */
}
		

/* dump contents of array to stdout */
int dumparray(float *array, int arraysize)
{
	int i;
	for (i=0; i < arraysize; i++)
		printf("%lf\n", array[i]);
		
	return 0;
}

/*Removes any negative values in the HOD array.  These values are noise in the spectrometer and really 
  screws up delta values if one gets through */	

int remove_d_noise(float *array, int arraysize, float low_threshold, float high_threshold) 
{
	int i;
	for (i=0; i < arraysize; i++) {
		if (array[i] < low_threshold) {
			if (i < 1 ) array[i] = low_threshold; 
			else array[i] = array[i-1];
		}
		if (array[i] > high_threshold) {
			if (i < 1 ) array[i] = high_threshold;
			else array[i] = array[i-1];
		}
	}	
	return 0;
}

/*Calculates hydrogen isotopic compsotion of water in eq with vapour given the D/H of vapour
	and the temperature.  Uses majuobe 1971 to calculate equilibrium fractionation factors*/

float get_dh_w(float dh, float t)
{
	
	float alpha =  exp((24844/(t*t)) - (76.248/t) + 0.052612);
	/* printf("alpha = %f\n", alpha); */
	return alpha * dh;


}
/*Calculates oxygen isotopic compsotion of water in eq with vapour given the 18O/16O of vapour
	and the temperature.  Uses majuobe 1971 to calculate equilibrium fractionation factors*/

float get_1816_w(float o18o16, float t)
{
	
	float alpha =  exp((1137/(t*t)) - (0.4156/t) - 0.0020667);
	/*printf("alpha = %f\n", alpha); */
	return alpha * o18o16;


}

float get_alpha_h(float t)
{
	
	return   exp((24844/(t*t)) - (76.248/t) + 0.052612);
	

}

float get_alpha_o(float t)
{
	
	return exp((1137/(t*t)) - (0.4156/t) - 0.0020667);
	

}
