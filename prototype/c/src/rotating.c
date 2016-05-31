// Gabriela Cavalcante

#include <opencv/cv.h>
#include <opencv/highgui.h>

// https://reecon.wordpress.com/2010/05/25/rotating-image-using-opencv/

IplImage* rotateImage(IplImage* image, float angle)
{ 

	int width = image->width;
	int height = image->height;

	IplImage *rotatedImage = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, image->nChannels);
     
    CvPoint2D32f center;
	center.x = width/2.0f;
	center.y = height/2.0f; 
 
    CvMat* mapMatrix = cvCreateMat(2, 3, CV_32FC1);
 	
 	/*
	center (MCvPoint2D32f)
		Center of the rotation in the source image.
	angle (Double)
		The rotation angle in degrees. Positive values mean couter-clockwise rotation (the coordiate origin is assumed at top-left corner).
	scale (Double)
		scale factor
	mapMatrix (IntPtr)
		Pointer to the destination 2x3 matrix of floating-point numbers	
 	*/
    cv2DRotationMatrix(center, angle, 1.0, mapMatrix);
    cvWarpAffine(image, rotatedImage, mapMatrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
    
    cvReleaseImage(&image);
    cvReleaseMat(&mapMatrix);
 
    return rotatedImage;
}

int main(int argc, char** argv)
{ 
	IplImage* image = cvLoadImage("../resources/street.jpg", 1); 
	
	cvNamedWindow( "Display", CV_WINDOW_AUTOSIZE );//Create and Name the window 

	cvShowImage( "Display", rotateImage(image, 120));//Display the image
	 
	cvWaitKey(0);//wait until user hits a key,if number is +ve then that much milli seconds image will wait to be closed
	
	cvDestroyWindow( "Display" );//Destroy and De-allocate memory
	
	return 0;
}