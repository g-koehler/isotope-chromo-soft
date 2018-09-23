/*  help.c

 Barfs out the help.

 */
 #include "dh.h"

int help(void)
{
	printf("Usage:  dh2 -f [FILE] [OPTION]\n\n");
	printf("            -t   threshold  [VALUE] 0-5000 peak identification threshold\n");
	printf("            -p   baseline percent   [VALUE] 0-100 peak identification threshold\n");
	printf("            -r   use 1st peak as reference  \n");
	printf("            -d   DeltaD value of ref   [VALUE] \n");
	printf("            -o   DeltaO value of ref   [VALUE] \n");
	printf("            -s   smooth peaks 0-boxcar, 1-savitsky golay \n");
	printf("            -b   boxcar size  [VALUE] \n");
	printf("            -w   report values as water in eq with vapour \n");
	printf("            -T   temperature of eq (above)   [VALUE] \n");
	printf("            -m   remove memory effect for [VALUE] seconds of sample peaks \n");	
	
	
	
	return 0;
}
