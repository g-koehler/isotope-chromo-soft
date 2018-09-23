/*  readfile.c - 	routine to read in file mass spec columns 44, 45, 46 at 
*                       regular intervals
*	
*	written by G. Koehler
*	
*	April , 2011
*	
*/

#include "co2.h"

int readfile(char *filename)
{

	
	FILE *input;
	int  i, j, ch;
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
    
    mass44 = (float *) malloc(number_of_lines * sizeof(float));
	
	if (mass44 == NULL) {
		fprintf(stderr, "initarray:  cannot allocate memory for array mass44\n");
		exit(-1);
        }
   mass45 = (float *) malloc(number_of_lines * sizeof(float));
        
    if (mass45 == NULL) {
        fprintf(stderr, "initarray:  cannot allocate memory for array mass45\n");
        exit(-1);
    }
    
    mass46 = (float *) malloc(number_of_lines * sizeof(float));
        
    if (mass46 == NULL) {
        fprintf(stderr, "initarray:  cannot allocate memory for array mass46\n");
        exit(-1);
    }

    

	/* printf("Number of lines = %d\nloading array..", number_of_lines); */
    
    for (i=0; i<4; i++)
        fgets(inputline, sizeof(inputline), input); /* read in header  */
	
	for (j=0; j < number_of_lines+4; j++) 
		fscanf (input, "%f,%f,%f,", mass44+j, mass45+j, mass46+j);
		
 
	/* printf("done.\n"); */
	
	fclose(input);
	 
	return 0;

} /* end readfile */


