#ifndef __IMGUTILS_H__
#define __IMGUTILS_H__

///
/// Creates a BMP file by B/W data
///
void BMPwrite(const char * fname, unsigned char *data, unsigned int width, unsigned int height);

///
/// Reads a BMP file onto a buffer, and returns it.
/// It is programmers' responsibility to deallocate the buffer
///
unsigned char * BMPread(const char *fname, unsigned int *width, unsigned int *height);


///
/// Create a height x width gaussian kernel.
/// TODO Fix this, it does not work properly
///
void getGaussian(int height, int width, double sigma);

#endif
