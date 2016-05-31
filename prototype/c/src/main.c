#include <stdio.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <opencv2/imgcodecs/imgcodecs_c.h> 

int main(){
	IplImage * img = cvLoadImage("../resources/street.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (!img) printf("non");
	cvNamedWindow("image", CV_WINDOW_AUTOSIZE);
	cvShowImage("image", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	printf("Hello world!");
	return 0;
}