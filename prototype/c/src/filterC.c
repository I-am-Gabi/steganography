// BOOK Learning OpenCV 3

//HighGUI is a toolkit with utilities for reading image files
#include <opencv/highgui.h>

int main( int argc, char** argv ) {
	/*
	This line loads the image.* 
	The function cvLoadImage() is a high-level routine that determines 
	the file format to be loaded based on the file name; 
	it also automatically allocates the memory needed for the image data structure. 
	cvLoadImage can read BMP, DIB, JPEG, JPE, PNG, PBM, PGM, PPM, SR, RAS, and TIFF
	A pointer to an allocated image data structure is then returned.
	This structure, called IplImage, is the OpenCV construct with which you will 
	deal the most. OpenCV uses this structure to handle all kinds of images: 
	single-channel, multichannel, integer-valued, floating-point-valued, et cetera. 
	*/
	IplImage* img = cvLoadImage("../resources/street.jpg", 0);  
	/*
	We use the pointer that cvLoadImage() returns to manipulate the image and the image data.
	Another high-level function, cvNamedWindow(), opens a window on the screen that can contain
	and display an image. This function, provided by the HighGUI library, also assigns 
	a name to the window (in this case, “Example1”).
	The second argument to cvNamedWindow() defines window properties. It may be set either to 0 
	(the default value) or to CV_WINDOW_AUTOSIZE. In the former case, the size of the window 
	will be the same regardless of the image size, and the image will be scaled to fit within the window. I
	*/
	cvNamedWindow( "Example1", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Example1", img );
	/*
	The cvWaitKey() function asks the program to stop and wait for a keystroke. If a positive argument is given,
	the program will wait for that number of milliseconds and then con- tinue even if nothing is pressed. 
	If the argument is set to 0 or to a negative number, the program will wait indefinitely for a keypress.
	*/
	cvWaitKey(0);
	/*
	Once we are through with an image, we can free the allocated memory. OpenCV expects a pointer to the IplImage* 
	pointer for this operation. After the call is completed, the pointer img will be set to NULL.
	*/
	cvReleaseImage( &img );
	/*
	Finally, we can destroy the window itself. The function cvDestroyWindow() will close the window and 
	de-allocate any associated memory usage (including the window’s internal image buffer, which is 
	holding a copy of the pixel information from *img).
	*/
	cvDestroyWindow( "Example1" );
}

