// Gabriela Cavalcante
// http://stackoverflow.com/questions/15686277/convert-rgb-to-grayscale-in-c
// https://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <stdio.h>
 
/*
	This code was make with the functions of OpenCV to change from rgb to binary
*/
int toBinary(IplImage* rgb)
{ 
	IplImage *gray = cvCreateImage(cvSize(rgb->width,rgb->height), 8, 1);
	 
	//Change from RGB to GrayScale
	cvCvtColor(rgb, gray, CV_RGB2GRAY); 
	IplImage *binary = cvCloneImage(gray);
	 
	cvNamedWindow("RGB:", 1);
	cvShowImage("RGB:", rgb);
	 
	cvNamedWindow("Grayscale:", 1);
	cvShowImage("Grayscale:", gray);
	 
	//Change from Grayscale to Binary
	/*
		src – input array (single-channel, 8-bit or 32-bit floating point).
		dst – output array of the same size and type as src.
		thresh – threshold value.
		maxval – maximum value to use with the THRESH_BINARY and THRESH_BINARY_INV thresholding types.
		type – thresholding type (see the details below).
	*/
	cvThreshold(gray, binary, 80, 255, CV_THRESH_BINARY);  
	cvNamedWindow("Binary:", 1);
	cvShowImage("Binary:", binary);
	 
	cvWaitKey(0);
	 
	cvDestroyWindow("RGB:");
	cvReleaseImage(&rgb);
	cvDestroyWindow("Grayscale:");
	cvReleaseImage(&gray);
	cvDestroyWindow("Binary:");
	cvReleaseImage(&binary);
	return 0;
}

// convert a sRGB component to linear format
double sRGB_to_linear(double x) {
    if (x < 0.04045) return x/12.92;
    return pow((x+0.055)/1.055, 2.4);
}

// apply the sRGB gamma correction again
double linear_to_sRGB(double y) {
    if (y <= 0.0031308) return 12.92 * y;
    return 1.055 * pow(y, 1/2.4) - 0.055;
} 

/*
	This is the version make for us to change de image
*/
int nb(IplImage* img, double k) {

	// new image
	IplImage *imgNew = cvCreateImage(cvSize(img->width,img->height), IPL_DEPTH_8U, 1);

	// setup the pointer to access img data 
	uchar *pImg   = ( uchar* )img->imageData;
	uchar *pImgNew   = ( uchar* )imgNew->imageData;

	int red, green, blue;
	for(int i = 0; i < img->height ; i++) {
		for(int j = 0; j < img->width ; j++) {

			red = pImg[i*img->widthStep + j*img->nChannels + 2];
			green = pImg[i*img->widthStep + j*img->nChannels + 1];
			blue = pImg[i*img->widthStep + j*img->nChannels + 0];

			double R_linear = sRGB_to_linear(red/255.0);
			double G_linear = sRGB_to_linear(green/255.0);
			double B_linear = sRGB_to_linear(blue/255.0);
			double gray_linear = 0.2126 * R_linear + 0.7152 * G_linear + 0.0722 * B_linear;

			double gray_color = round(linear_to_sRGB(gray_linear) * 255);

			int blackORwhite;
			if (gray_color >= k) blackORwhite = 1;
			else blackORwhite = 0;

			printf("%f\n", blackORwhite);
			pImgNew[i*imgNew->widthStep + j] = gray_color;  
			blackORwhite = 0;	
		}
	}

	cvNamedWindow("NB:", CV_WINDOW_AUTOSIZE);
	cvShowImage("NB:", imgNew);
	cvWaitKey(0);
	cvDestroyWindow("NB:");
	cvReleaseImage(&imgNew); 

	return 0;
}

int main( void )
{ 
  IplImage* image = cvLoadImage("../resources/street.jpg", 1); 
  nb(image, 80);
  return 0;
}