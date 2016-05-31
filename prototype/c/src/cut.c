// Gabriela Cavalcante

// http://stackoverflow.com/questions/11725990/opencv-get-subimage-in-c

#include <opencv/cv.h>
#include <opencv/highgui.h>

int cut(IplImage * img1) {

	/* Sets an image Region Of Interest (ROI) for a given rectangle.
	   Note that the rectangle area has to be __INSIDE__ the image */
	cvSetImageROI(img1, cvRect(25, 25, img1->width/2, img1->height/2));

	/* create destination image
	   Note that cvGetSize will return the width and the height of ROI */
	IplImage *img2 = cvCreateImage(cvGetSize(img1),
	                               img1->depth,
	                               img1->nChannels);

	/* copy subimage */
	cvCopy(img1, img2, NULL);

	/* always reset the Region of Interest */
	cvResetImageROI(img1);

	cvNamedWindow("Cut:", 1);
	cvShowImage("Cut:", img2);

	cvWaitKey(0);
	 
	cvDestroyWindow("Cut:");
	cvReleaseImage(&img2);

	return 0;
}

int main( void )
{ 
  IplImage* image = cvLoadImage("../resources/street.jpg", 1); 
  cut(image);
  return 0;
}