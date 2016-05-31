#include "../../includes/image.h"

IplImage* readImage(const char* filename) {
    IplImage* img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED); 
    return img;
}

void saveImage(const char* filename, IplImage* img) {
    cvSaveImage(filename, &img, NULL);
}