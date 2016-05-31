// BOOK Learning OpenCV 3

/*
One particularly simple operation is the smoothing of an image, 
which effectively reduces the information content of the image 
by convolving it with a Gaussian or other similar kernel function. 
OpenCV makes such convolutions exceptionally easy to do. We can 
start by creating a new window called “Example4-out”, where we
 can display the results of the processing. Then, after we have 
 called cvShowImage() to display the newly captured frame in the 
 input window, we can compute and display the smoothed image in 
 the output window. 
*/ 
#include <opencv/cv.h>
#include <opencv/highgui.h>

void smoothing () { 
   	IplImage* image = cvLoadImage("../resources/street.jpg", 0); 
 
	cvNamedWindow( "SmoothingOut", CV_WINDOW_AUTOSIZE); 
	
	/*
	The smoothing operation is itself just a single call to the OpenCV 
	library: we specify the input image, the output image, the smoothing 
	method, and the parameters for the smooth. In this case we are 
	requesting a Gaussian smooth over a 3 × 3 area centered on each pixel. 
	*/
	cvSmooth( image, image, CV_GAUSSIAN, 3, 3, 1, 1);  

	// Show the smoothed image in the window
	cvShowImage("SmoothingOut", image );
 

	// Wait for the user to hit a key, then clean up the windows
	cvWaitKey(0);
	cvDestroyWindow( "SmoothingIn" ); 	
}

int main(int argc, char** argv)
{ 
	smoothing();
	return 0;
}