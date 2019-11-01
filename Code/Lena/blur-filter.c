#include <stdio.h>
#include <stdlib.h>
#include "imgutils.h"

#define _printf printf

#define KERNEL_SIZE 5

#if KERNEL_SIZE == 5
float kernel[KERNEL_SIZE][KERNEL_SIZE] =
{
	{ 1/44., 1/44., 2/44., 1/44., 1/44. },
	{ 1/44., 2/44., 3/44., 2/44., 1/44. },
	{ 2/44., 3/44., 4/44., 3/44., 2/44. },
	{ 1/44., 2/44., 3/44., 2/44., 1/44. },
	{ 1/44., 1/44., 2/44., 1/44., 1/44. },
};
#elif KERNEL_SIZE == 3
float kernel[KERNEL_SIZE][KERNEL_SIZE] =
{
	{ 1/16., 2/16., 1/16. },
	{ 2/16., 4/16., 2/16. },
	{ 1/16., 2/16., 1/16. }
};
#endif

int main()
{
	const char * in_file = "lena-bw.bmp";
	const char * outfile = "output.bmp";
#if 1
	unsigned int width, height;
	unsigned char * inputimg = BMPread(in_file, &width, &height);
#else	
	unsigned int width = 16, height = 16;
	unsigned char inputimg [64] =
	{
		0, 1, 1, 0, 1, 2, 2, 1, 1, 2, 2, 1, 0, 1, 1, 0,
		0, 1, 1, 0, 1, 2, 2, 1, 1, 2, 2, 1, 0, 1, 1, 0,
		0, 1, 1, 0, 1, 2, 2, 1, 1, 2, 2, 1, 0, 1, 1, 0,
		0, 1, 1, 0, 1, 2, 2, 1, 1, 2, 2, 1, 0, 1, 1, 0,
		0, 1, 1, 0, 1, 2, 2, 1, 1, 2, 2, 1, 0, 1, 1, 0,
		0, 1, 1, 0, 1, 2, 2, 1, 1, 2, 2, 1, 0, 1, 1, 0,
		0, 1, 1, 0, 1, 2, 2, 1, 1, 2, 2, 1, 0, 1, 1, 0,
		0, 1, 1, 0, 1, 2, 2, 1, 1, 2, 2, 1, 0, 1, 1, 0,
	};
#endif
	unsigned char *outputimg = (unsigned char *) malloc(width * height * sizeof(unsigned char));
	
	int kend = KERNEL_SIZE / 2, kstart = -kend;
	printf("kstart %d kend %d\n", kstart, kend);
	
	for(int y=0; y<height; y++)
		for(int x=0; x<width; x++)
		{
			float acc = 0.;
			for(int ky = 0; ky < KERNEL_SIZE; ky++)
				for(int kx = 0; kx < KERNEL_SIZE; kx ++)
				{
					int py = y + ky - KERNEL_SIZE * 2;
					int px = x + kx - KERNEL_SIZE * 2;
					//printf("y %d x %d ky %d kx %d py %d px %d", y, x, ky, kx, py, px);
					if(px >= 0 && py >= 0)
					{
						float in = (float) inputimg[py * width + px];
						float k = kernel[ky][kx];
						float res = in * k;
						acc +=  res;
						//printf("-> in %f k(%d, %d) %f res %f acc %f", in, ky, kx, k, res, acc);
					}
					//printf("\n");
				}
			outputimg[y * width + x] = acc;
		}
	
	
    BMPwrite(outfile, &outputimg[0], width, height);
	
	free(inputimg);
}