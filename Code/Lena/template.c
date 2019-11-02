#include <stdio.h>
#include <stdlib.h>
#include "imgutils.h"


int main()
{
	const char *in_file = "lena-bw.bmp";
	const char *outfile = "output.bmp";
	
	unsigned int width, height;
	unsigned char * inputimg = BMPread(in_file, &width, &height);
	
	
	
    BMPwrite(outfile, &inputimg[0], width, height);
	
	free(inputimg);
}