// Gabriela Cavalcante

#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage* doPyrDown(IplImage* in, int filter) {  

   	IplImage* image = cvLoadImage("../resources/street.jpg", 0); 

   	// Best to make sure input image is divisible by two
 	assert( in->width%2 == 0 && in->height%2 == 0);

 	/*
		In OpenCV, all of the important data types are implemented as 
		structures and passed around as structure pointers.
 	*/
 	IplImage* out = cvCreateImage(
 		cvSize( in->width/2, in->height/2),
 		in->depth,
 		in->nChannels
 		);
 	cvPyrDown(in, out, filter);

 	return(out);
} 

int main(int argc, char** argv)
{ 
	IplImage* image = cvLoadImage("../resources/street.jpg", 1); 
	cvNamedWindow( "Display", CV_WINDOW_AUTOSIZE );//Create and Name the window 

	cvShowImage( "Display", doPyrDown(image, CV_GAUSSIAN_5x5));//Display the image
	 
	cvWaitKey(0);//wait until user hits a key,if number is +ve then that much milli seconds image will wait to be closed
	
	cvDestroyWindow( "Display" );//Destroy and De-allocate memory
	
	return 0;
}