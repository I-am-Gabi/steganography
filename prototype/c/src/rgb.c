// Gabriela Cavalcante

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>

void mouseEvent(int evt, int i, int j, int flags, void* param){ 
    IplImage* rgb = (IplImage*) param;

    if(evt==CV_EVENT_MOUSEMOVE)
    {

    	int height     = rgb->height;
		int width      = rgb->width;
		int step       = rgb->widthStep/sizeof(uchar);
		int channels   = rgb->nChannels;
		uchar* data    = (uchar *)rgb->imageData;
		
		unsigned char r = data[i * step + j * channels + 2];
		unsigned char g = data[i * step + j * channels + 1];
		unsigned char b = data[i * step + j * channels + 0]; 
		 
        printf("Current Position: x= %d y= %d B= %d G= %d R= %d\n", i , j , b , g , r);
    }
}

int main() {
	cvNamedWindow("rgb", CV_WINDOW_AUTOSIZE); 
	IplImage* rgb = cvLoadImage("../resources/street.jpg", 1);

	while(1){ 
		cvShowImage("rgb", rgb); 

		cvSetMouseCallback("rgb", mouseEvent, (void*) rgb);
		
		char c = cvWaitKey(33);
		if( c == 27 ) break;
	}

	cvDestroyWindow( "rgb" );
}
