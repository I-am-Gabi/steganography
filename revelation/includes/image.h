#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <stdio.h>
#include <opencv/highgui.h> 

IplImage* readImage(const char* filename);

void saveImage(const char* filename, IplImage* img);

#endif