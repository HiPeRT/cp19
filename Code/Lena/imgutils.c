#include<stdio.h>
#include <stdlib.h>

#include <math.h>

#define fileHeaderSize 40
#define bmpHeaderSize 14
#define noColor 256
unsigned char bitmap[1024 * 1024 + fileHeaderSize + bmpHeaderSize + noColor * 4];

void put_in_char_arr(unsigned char * dst, unsigned int size, unsigned int val)
{
	for(int i=0; i<size; i++)
	{
		//printf("i=%d shifto di %d\n", i, i << 3); 
		dst[i] = val >> (i << 3) & 0xff;
	}
}

unsigned int read_from_char_arr(unsigned char *src)
{
	unsigned int retval = 0;
	
	for(int i=0; i<4; i++)
		retval += (src[i] << (i << 3));
	
	return retval;
}

unsigned int compute_fsize(unsigned int width, unsigned int height)
{
	return 40 + 14 + noColor * 4 + width * height;
}

unsigned char* BMPmake(unsigned int width, unsigned int height, unsigned char *img)
{
    int i, end_color = 54 + 4 * noColor;
	unsigned int image_size = width * height;
	unsigned int file_size = compute_fsize(width, height);
	
    // -- FILE HEADER -- //

    // bitmap signature
    bitmap[0] = 'B';
    bitmap[1] = 'M';

    // file size
	//printf("file_size is %d 0x%x\n", file_size, file_size);
	put_in_char_arr(&bitmap[2], 4, file_size);
	
    // reserved field (in hex. 00 00 00 00)
    for( i = 6; i < 10; i++) bitmap[i] = 0;

    // offset of pixel data inside the image
    //The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found.
    //here 1078
	//printf("end_color is %d 0x%x\n", end_color, end_color);
	put_in_char_arr(&bitmap[10], 4, end_color);

    // -- BITMAP HEADER -- //

    // header size
    bitmap[14] = 40;
    for( i = 15; i < 18; i++) bitmap[i] = 0;

    // width of the image
	//printf("width is %d 0x%x\n", width, width);
	put_in_char_arr(&bitmap[18], 4, width);

    // height of the image
	//printf("width is %d 0x%x\n", height, height);
	put_in_char_arr(&bitmap[22], 4, height);

    // no of color planes, must be 1
    bitmap[26] = 1;
    bitmap[27] = 0;

    // number of bits per pixel
    bitmap[28] = 8; // 1 byte
    bitmap[29] = 0;

    // compression method (no compression here)
    for( i = 30; i < 34; i++) bitmap[i] = 0;

    // size of pixel data
	//printf("image_size is %d 0x%x\n", image_size, image_size);
	put_in_char_arr(&bitmap[34], 4, image_size);

    // horizontal resolution of the image - pixels per meter (2835)
    bitmap[38] = 0;
    bitmap[39] = 0;
    bitmap[40] = 0;
    bitmap[41] = 0;

    // vertical resolution of the image - pixels per meter (2835)
    bitmap[42] = 0;
    bitmap[43] = 0;
    bitmap[44] = 0;
    bitmap[45] = 0;

    // color palette information here 256
	put_in_char_arr(&bitmap[46], 4, noColor);

    // number of important colors
    // if 0 then all colors are important
    for( i = 50; i < 54; i++) bitmap[i] = 0;

    //Color Palette
    //for less then or equal to 8 bit BMP Image we have to create a 4*noofcolor size color palette which is nothing but
    //[BLUE][GREEN][RED][ZERO] values
    //for 8 bit we have the following code
    static unsigned char temp = 0;
    for (i = 54; i < end_color; i += 4)
    {
        bitmap[i]   = temp;
        bitmap[i+1] = temp;
        bitmap[i+2] = temp;
        bitmap[i+3] = 0;
        temp ++;
    }

    // -- PIXEL DATA -- //
    for(i = 0; i < image_size; i++)
	{
		unsigned int idx = end_color + i;
		bitmap[idx] = img[i];
	}
	return &bitmap[0];
}

void BMPwrite(const char * fname, unsigned char *data, unsigned int width, unsigned int height)
{
    unsigned char * filedata = BMPmake(width, height, &data[0]);
	unsigned int file_size = compute_fsize(width, height);
    //use wb+ when writing to binary file .i.e. in binary form whereas w+ for txt file.
    FILE *file = fopen(fname, "wb+");
    for(int i = 0; i < file_size; i++)
    {
        fputc(filedata[i], file);
    }
    fclose(file);
}

unsigned char * BMPread(const char *fname, unsigned int *width, unsigned int *height)
{
	unsigned int fSize = compute_fsize(1024, 1024);
	//printf("fSize is %d\n", fSize);

	unsigned char *buf = (unsigned char *) malloc(fSize * sizeof(unsigned char));
	
	FILE *file = fopen(fname, "rb");
	for(int i = 0; i < fSize; i++)
    {
        buf[i] = fgetc(file);
    }
	fclose(file);
	
	*width = read_from_char_arr(&buf[18]);
	*height = read_from_char_arr(&buf[22]);
	unsigned int image_size = read_from_char_arr(&buf[34]);
	
	//printf("image_size is %d\n", image_size);
    int dataptr = 54 + 4 * noColor;
	unsigned char *outimg = (unsigned char *) malloc(*width * *height * sizeof(unsigned char));
	for(int i=0; i<image_size; i++)
		outimg[i] = buf[i + dataptr];
	
	free(buf);
	return outimg;
}

// This does not work properly
void getGaussian(int height, int width, double sigma)
{
    // double sum=0.0;
    // int i,j;

    // for (i=0 ; i<height ; i++) {
        // for (j=0 ; j<width ; j++) {
            // kernel[i][j] = exp(-(i*i+j*j)/(2*sigma*sigma))/(2*M_PI*sigma*sigma);
            // sum += kernel[i][j];
        // }
    // }

    // for (i=0 ; i<height ; i++) {
        // for (j=0 ; j<width ; j++) {
            // kernel[i][j] /= sum;
        // }
    // }

    // return kernel;
}
