// Gabriela Cavalcante

#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage* zoom(IplImage* image, int percent) {

  // declare a destination IplImage object with correct size, depth and channels
  IplImage *destination = cvCreateImage
    (cvSize((int)
      ((image->width*percent)/100), 
      (int)((image->height*percent)/100)),
      image->depth, image->nChannels);

  //use cvResize to resize image to a destination image
  cvResize(image, destination, CV_INTER_LINEAR);

  return destination;

}

/**
 * @function main
 */
int main( void )
{ 
  IplImage* image = cvLoadImage("../resources/street.jpg", 1); 
  
  cvNamedWindow( "Display", CV_WINDOW_AUTOSIZE );//Create and Name the window 

  cvShowImage( "Display", zoom(image, 20));//Display the image
   
  cvWaitKey(0);//wait until user hits a key,if number is +ve then that much milli seconds image will wait to be closed
  
  cvDestroyWindow( "Display" );//Destroy and De-allocate memory
  
  return 0;
}