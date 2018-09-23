

/*  INCLUDES   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

/*  DEFINES   */


#define TRUE 		1
#define FALSE		0
#define THRESHOLD	1000


/*  GLOBALS   */


float *major, *minor;


   /* headamp resistor structure */

int sigma, debuglevel, print_flag;
long int mainarraysize;

/*  FUNCTION PROTOTYPES  */


		
int boxcar_smooth(float *array, int arraysize, int boxcarsize);

int readfile(char *filename);

float array_max(float *array, int arraysize);

int baseline_norm(float *array, int arraysize, float percent);

float getsum(float *array, int arraysize, float percent);

float dumparray(float *array, int arraysize);

int remove_d_noise(float *array, int arraysize);

float get_dh_w(float dh, float t);

float get_1816_w(float o18o16, float t);

int smooth_sg(float *array, int arraysize);

float trapz(float *array, int arraysize, float percent);

float simpz(float *array, int arraysize, float percent);

float o17_corr(float d45, float d46);

float craig_o(float d46, float d13C);

int readamp(void);
