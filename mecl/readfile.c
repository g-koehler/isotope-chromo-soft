/*  readfile.c - 	routine to read in file mass spec columns 44, 45, 46 at 
*                       regular intervals
*	
*	written by G. Koehler
*	
*	April , 2011
*	modified for mecl or any other two collector continuous flow measurement
*	Oct, 2011
*/

#include "mecl.h"

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
    
    major = (float *) malloc(number_of_lines * sizeof(float));
	
	if (major == NULL) {
		fprintf(stderr, "initarray:  cannot allocate memory for array mass44\n");
		exit(-1);
        }
   minor = (float *) malloc(number_of_lines * sizeof(float));
        
    if (minor == NULL) {
        fprintf(stderr, "initarray:  cannot allocate memory for array mass45\n");
        exit(-1);
    }
    

    

	/* printf("Number of lines = %d\nloading array..", number_of_lines); */
    
    for (i=0; i<4; i++)
        fgets(inputline, sizeof(inputline), input); /* read in header  */
	
	for (j=0; j < number_of_lines+4; j++) 
		fscanf (input, "%f,%f", major+j, minor+j);
		
 
	/* printf("done.\n"); */
	
	fclose(input);
	 
	return 0;

} /* end readfile */


