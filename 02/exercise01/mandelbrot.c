#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]){
	for(int i = 0; i < Y; i++){
		for(int j = 0; j < X; j++){
			double x0 = (double)j / X * 3.5 - 2.5;
			double y0 = (double)i / Y * 2 - 1;
			double x = 0, y = 0;
			int iter = 0;
			while(x*x + y*y <= 2*2 && iter < MAX_ITER){
				double xtemp = x*x - y*y + x0;
				y = 2*x*y + y0;
				x = xtemp;
				iter++;
			}
			image[i][j] = iter % 256;
		}
	 }
}

int main() {
	uint8_t image[Y][X];

	calc_mandelbrot(image);

	const int channel_nr = 1, stride_bytes = 0;
	stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
	return EXIT_SUCCESS;
}