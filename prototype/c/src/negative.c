// Gabriela Cavalcante

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
 
// https://codezone4.wordpress.com/2013/02/03/create-negative-image-using-opencv/
 
int negative(IplImage* image)
{ 
	IplImage *dest = cvCloneImage(image);
	 
	cvNamedWindow("Original:", 1);
	cvShowImage("Original:", image);
	 
	cvNot(image, dest); //Create a negative image from source image
	cvNamedWindow("Negative:", 1);
	cvShowImage("Negative:", dest);
	 
	cvWaitKey(0);
	 
	cvDestroyWindow("Original:");
	cvReleaseImage(&image);

	cvDestroyWindow("Negative:");
	cvReleaseImage(&dest);

	return 0;
}
 
int main( void )
{ 
  IplImage* image = cvLoadImage("../resources/street.jpg", 1); 
  negative(image);
  return 0;
}