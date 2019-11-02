#include <stdio.h>
#include <stdlib.h>

#include "imgutils.h"

//#define _printf(...) printf(__VA_ARGS__)
#define _printf(...)

#define KERNEL_SIZE 7

#if KERNEL_SIZE == 7

float kernel[KERNEL_SIZE][KERNEL_SIZE] =
{
	{ 1., 1., 1., 2., 1., 1., 1. },
	{ 1., 1., 2., 2., 2., 1., 1. },
	{ 1., 2., 3., 3., 3., 2., 1. },
	{ 2., 2., 3., 4., 3., 2., 2. },
	{ 1., 2., 3., 3., 3., 2., 1. },
	{ 1., 1., 2., 2., 2., 1., 1. },
	{ 1., 1., 1., 2., 1., 1., 1. },
};
unsigned int coeff = 84;

#elif KERNEL_SIZE == 5

float kernel[KERNEL_SIZE][KERNEL_SIZE] =
{
	{ 1.,  4.,  7.,  4., 1. },
	{ 4., 16., 26., 16., 4. },
	{ 7., 26., 41., 26., 7. },
	{ 4., 16., 26., 16., 4. },
	{ 1.,  4.,  7.,  4., 1. },
};
unsigned int coeff = 273;

#elif KERNEL_SIZE == 3

float kernel[KERNEL_SIZE][KERNEL_SIZE] =
{
	{ 1., 2., 1. },
	{ 2., 4., 2. },
	{ 1., 2., 1. }
};
unsigned int coeff = 16;

#endif


int main()
{
	const char * in_file = "lena-bw.bmp";
	const char * outfile = "output.bmp";
	unsigned int width, height;
	unsigned char * inputimg = BMPread(in_file, &width, &height);

	unsigned char *outputimg = (unsigned char *) malloc(width * height * sizeof(unsigned char));
	
	_printf("Kernel size %d x %d\n", KERNEL_SIZE, KERNEL_SIZE);
	
	for(int y=0; y<height; y++)
		for(int x=0; x<width; x++)
		{
			float acc = 0.;
			for(int ky = KERNEL_SIZE / -2; ky < KERNEL_SIZE / 2; ky++)
				for(int kx = KERNEL_SIZE / -2; kx < KERNEL_SIZE / 2; kx ++)
				{
					int py = y + ky;
					int px = x + kx;
					_printf("y %d x %d ky %d kx %d py %d px %d", y, x, ky, kx, py, px);
					if(px >= 0 && py >= 0)
					{
						float in = (float) inputimg[py * width + px];
						float k = kernel[ky + KERNEL_SIZE / 2][kx + KERNEL_SIZE / 2];
						float res = in * k;
						acc +=  res;
						_printf("-> in %f k(%d, %d) %f res %f acc %f", in, ky, kx, k, res, acc);
					}
					_printf("\n");
				}
			outputimg[y * width + x] = acc / coeff;
		}
	
	
    BMPwrite(outfile, &outputimg[0], width, height);
	
	free(inputimg);
	
	return 0;
}