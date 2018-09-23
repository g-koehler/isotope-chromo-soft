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
		printf("%d  %f\n",i, array[i]);
		
	return 0;
}

/*Removes any negative values in the HOD array.  These values are noise in the spectrometer and really 
  screws up delta values if one gets through */	

int remove_d_noise(float *array, int arraysize) 
{
	int i;
	for (i=0; i < arraysize; i++) {
		if (array[i] < 0) array[i] = 0.1;
		if (array[i] > 100) array[i] = 60.0;
	}	
	return 0;
}

/*Calculates hydrogen isotopic compsotion of water in eq with vapour given the D/H of vapour
	and the temperature.  Uses majuobe to calculate equilibrium fractionation factors*/

float get_dh_w(float dh, float t)
{
	
	float alpha =  exp((24844/(t*t)) - (76.248/t) + 0.052612);
	/*printf("alpha = %f\n", alpha); */
	return alpha * dh;


}
/*Calculates hydrogen isotopic compsotion of water in eq with vapour given the D/H of vapour
	and the temperature.  Uses majuobe to calculate equilibrium fractionation factors*/

float get_1816_w(float o18o16, float t)
{
	
	float alpha =  exp((1137/(t*t)) - (0.4156/t) + 0.0020667);
	/*printf("alpha = %f\n", alpha); */
	return alpha * o18o16;


}

/*Calculates d13C from d45 and d45 - from Brand et al 2010 17O correction */

float o17_corr(float d45, float d46) 
{
	return d45 + 0.070*(d45 - (0.528 * d46));

}

/* adjusts d46 for o17 from CO2 - from craig, 1957 */

float craig_o(float d46, float d13C)
{

	return (1.0014 * d46) + (0.009 * d13C);

}

int readamp (void) 
{
	return 0;

}
