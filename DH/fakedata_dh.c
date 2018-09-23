/*  	fakedata.c - a program to generate fake data that matches output of the LGR laser spetrometer
	
	May 11, 2011   Geoff Koehler
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define SCALE 	10000000
#define SIGMA 	10.0
#define MU 	0.0
#define XSIZE 	10000
#define SHIFT 	0
#define NOISELEVEL 1.0
#define RANSEED	-4
#define PEAKWIDTH 400
#define DH 0.000285
#define O18O16 0.001979

/* function prototypes */
float ran0(int *idum); 
float mkgauss(float x, float scale, float sigma, float mu);
void writeimage( void );

float *data_array, *peak;
int xsize;

int main (int argc, char *argv[])
{
	char c;
	int i, j, fitsflag, seed = RANSEED, peaksize, shift, blocks;
	FILE *outfile;
	float tempresult, scale, noiselevel, amplevel, sigma;
	
	scale = SCALE;
	noiselevel = NOISELEVEL;
	sigma = SIGMA;
	xsize = XSIZE;
	peaksize = PEAKWIDTH;
	amplevel = 0.0;
	fitsflag = 0;
	shift = SHIFT;
	
	/*parse command line  */
	
	while (( c=getopt(argc, argv, "a:s:n:S:x:y:f:")) != -1)
		switch (c)
		{
		case 'a':
			amplevel = atof(optarg);
			break;
		case 's':
			scale=atof(optarg);
			break;
		case 'n':
			noiselevel=atof(optarg);
			break;
		case 'S':
			sigma = atof(optarg);
			break;
		case 'x':
			xsize = atoi(optarg);
			break;
		case 'y':
			peaksize = atoi(optarg);
			break;
		case 'f':
			shift = atoi(optarg);
			break;
		
		default:
			break;
		
		}

	
	/* malloc data array  */
	
	data_array = (float *) malloc (xsize * sizeof(float));
	if (data_array == NULL) {
		fprintf(stderr, "error:  could not malloc main array\n");
		exit (-1);
	}
	peak = (float *) malloc (peaksize * sizeof(float));
	if (peak == NULL) {
		fprintf(stderr, "error:  could not malloc peak array\n");
		exit (-1);
	}
	
	/* fill data array with noise - */
	
	
	for (i=0; i < xsize; i++) {
			
			data_array[i] = amplevel + noiselevel * ran0(&seed);
		
	}
	/* fill peak array with peak */
		
	for (j=0; j < peaksize; j++) {
	
		tempresult = mkgauss((float)(j-peaksize/2), scale,
		sigma, MU);
		
		if (tempresult < 0.001) 
			peak[j] = amplevel + noiselevel * ran0(&seed);
		
		else 
			peak[j] = amplevel + tempresult + (noiselevel *
			ran0(&seed));
		
	}
	printf("peaksize is %d\n", peaksize);
	/* put peaks into array starting every 500 secs */

	blocks = (int) xsize/ (1000 + peaksize);

	for (i=0; i < blocks; i++) {

		for ( j = 0; j<1000+peaksize; j++) {
		
			if (j< peaksize) data_array[(1000 + peaksize)*i + j] += peak[j] + (noiselevel * ran0(&seed));
		}
	}
		
	
	/* open the file in STF format   */
	
	outfile = fopen("fakedata.txt", "w");
	
	if (outfile) {   
	
		
		
		for (i=0+shift; i < xsize - shift; i++) {
			fprintf(outfile, "%9.4f, %9.4f, %9.4f", data_array[i], data_array[i+shift]*O18O16, 
			data_array[i+shift]*DH);
			
			fprintf(outfile, "\n");  /* newline every row */
		}
		fclose(outfile);
	}
	else {
	
		perror("fakedata.stf");
	}
	
	return 0;
}

