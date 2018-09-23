/*  Integrate.c

 A peak integration routine.  Uses trapazoidal rule to integrate data in a floating point
 array

 */
 #include "co2.h"

float trapz(float *array, int arraysize, float percent)
{
	float temp[2], max, total = 0.0, baseline;
	int i, j;
    
    max = array_max(array, arraysize);
	
	baseline = max * (percent/100.0);

	for (i=0; i< arraysize; i++) {

		if (array[i] > baseline) {
	
			for (j = 0; j < 2; j++)  temp[j] = array[i+j]-baseline;
			total += temp[0] + ((temp[1]-temp[0])/2);
		}

	}

	/*printf("integrate.c :  total = %f\n", total); */
	return total;


}


/*  Simpsons rule to integrate */

float simpz(float *array, int arraysize, float percent)
{
	float temp[3], max, total = 0.0, baseline;
	int i, j;
    
    max = array_max(array, arraysize);
	
	baseline = max * (percent/100.0);

	for (i=0; i< arraysize; i++) {

		if (array[i] > baseline) {
	
			for (j = 0; j < 3; j++)  temp[j] = array[i+j]-baseline;
			total += ((temp[0]+4*temp[1] + temp[2])/3);
		}

	}

	/*printf("integrate.c :  total = %f\n", total); */
	return total;


}

/*  get simple sum of array above baseline in percent */

float getsum(float *array, int arraysize, float percent)
{
	float max, total = 0.0, baseline;
	int j;
    
    max = array_max(array, arraysize);
	
	baseline = max * (percent/100.0);
	
    for(j=0; j<arraysize; j++) {
        if (array[j] > baseline)
            total += array[j] - baseline;
    }
			
			
	
	return total;
}







