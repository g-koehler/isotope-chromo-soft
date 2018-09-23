/*  readfile.c - 	routine to read in file from LGR analyser
*	
*	written by G. Koehler
*	
*	April , 2011
*	
*/

#include "dh.h"

int readfile(char *filename)
{

	
	FILE *input;
	int  i, j, ch, check;
	long int number_of_lines = 0; 
	char inputline[255];	
		
   /* printf("processing input  file...\n"); */
    
   
    /* get number of lines in input file */
    input = fopen(filename, "r");
    if (input == NULL) {
		fprintf(stderr, "readfile: cant open %s\n", filename);
		exit(-1);
	}
    
    do 
    {
        ch = fgetc(input);
        if(ch == '\n')
            number_of_lines++;
    } while (ch != EOF);
    
   /*last line doesn't end with a new line!
    but there has to be a line at least before the last line */
    
    if(ch != '\n' && number_of_lines != 0) 
        number_of_lines++;
	
	mainarraysize = number_of_lines;
	
	rewind(input);		/* set file pointer to beginning of file */
    
    d = (float *) malloc(number_of_lines * sizeof(float));
	
	if (d == NULL) {
		fprintf(stderr, "initarray:  cannot allocate memory for array dh\n");
		exit(-1);
        }
   o18 = (float *) malloc(number_of_lines * sizeof(float));
        
    if (o18 == NULL) {
        fprintf(stderr, "initarray:  cannot allocate memory for array o18\n");
        exit(-1);
    }
    
    h2o = (float *) malloc(number_of_lines * sizeof(float));
        
    if (h2o == NULL) {
        fprintf(stderr, "initarray:  cannot allocate memory for array h2o\n");
        exit(-1);
    }

    

	/* printf("Number of lines = %d\nloading array..", number_of_lines); */
    
    for (i=0; i<4; i++)
        check = fgets(inputline, sizeof(inputline), input); /* read in header  */
	
	for (j=0; j < number_of_lines+4; j++) 
		check = fscanf (input, "%e,%e,%e,", h2o+j, o18+j, d+j);
		
 
	/* printf("done.\n"); */
	
	fclose(input);
	 
	return 0;

} /* end readfile */

	
