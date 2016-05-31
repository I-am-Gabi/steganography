// Gabriela Cavalcante

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <stdio.h>

/*
Convert between color spaces:
cvCvtColor(src,dst,code); // src -> dst

  code    = CV_<X>2<Y>
  <X>/<Y> = RGB, BGR, GRAY, HSV, YCrCb, XYZ, Lab, Luv, HLS

e.g.: CV_BGR2GRAY, CV_BGR2HSV, CV_BGR2Lab
*/
 
int toYcrcb(IplImage* rgb)
{ 	
	// IplImage* cvCreateImage(CvSize size, int depth, int channels);
	IplImage *imgYCR = cvCreateImage(cvSize(rgb->width,rgb->height), rgb->depth, rgb->nChannels);
	  
	// cvConvertImage(src, dst, flags=0);
	cvCvtColor(rgb, imgYCR, CV_RGB2YCrCb); //Change from RGB to YCR 
	 
	cvNamedWindow("RGB:", 1);
	cvShowImage("RGB:", rgb);
	 
	cvNamedWindow("YCR:", 1);
	cvShowImage("YCR:", imgYCR); 
	 
	cvWaitKey(0);
	 
	cvDestroyWindow("RGB:");
	cvReleaseImage(&rgb);
	cvDestroyWindow("YCR:");
	cvReleaseImage(&imgYCR); 
	return 0;
}

// RGB -> YCbCr
int toYcrcbDirect(IplImage* img) {
	IplImage *imgYCR = cvCreateImage(cvSize(img->width,img->height), img->depth, img->nChannels);

	// setup the pointer to access img data 
	uchar *pImg   = ( uchar* )img->imageData;
	uchar *pImgY   = ( uchar* )imgYCR->imageData;

	int rED, gREEN, bLUE, Y, Cr, Cb;
	float delta;

	if (img->depth == 8)
		delta = 128;
	else if (img->depth == 16)
		delta = 32768;
	else 
		delta = 0.5;

	for(int i = 0; i < img->height ; i++) {
		for(int j = 0; j < img->width ; j++) {

			rED = pImg[i*img->widthStep + j*img->nChannels + 2];
			gREEN = pImg[i*img->widthStep + j*img->nChannels + 1];
			bLUE = pImg[i*img->widthStep + j*img->nChannels + 0];

			Y = (0.299 * rED) + (0.587 * gREEN) + (0.114 * bLUE);
			Cr = (rED - Y) * 0.713 + delta;
			Cb = (bLUE - Y) * 0.564 + delta;

			pImgY[i*img->widthStep + j*img->nChannels + 2] = Y;  // red
			pImgY[i*img->widthStep + j*img->nChannels + 1] = Cb;  // green
			pImgY[i*img->widthStep + j*img->nChannels + 0] = Cr;  // blue
		}
	}
	
	cvNamedWindow("YCRCB", CV_WINDOW_AUTOSIZE); 
	cvShowImage("YCRCB", imgYCR);
	cvWaitKey(0);
	cvDestroyWindow("YCRCB:");
	cvReleaseImage(&imgYCR); 

	return 0;
}

int main( void )
{ 
  IplImage* image = cvLoadImage("../resources/street.jpg", 1); 
  toYcrcbDirect(image);
  return 0;
}