// Gabriela Cavalcante

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>

void getDataImage(IplImage* img) {   
	int height     = img->height;
	int width      = img->width;
	int step       = img->widthStep/sizeof(uchar);
	int channels   = img->nChannels; 
	int depth 	   = img->depth;
	int size 	   = img->imageSize;  
 
	printf("Wigth %d\n", width);  
	printf("Height %d\n", height);  
	printf("Pixel Depth %d\n", depth);  
	printf("Channels %d\n", channels);  
	printf("Wight Step %d\n", step);  
	printf("Image Size %d\n", size); 
}

int main(int argc, char** argv)
{ 
	IplImage* image = cvLoadImage("../resources/street.jpg", 1); 
	getDataImage(image);
	return 0;
}