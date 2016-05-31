#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <unistd.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 2
#define SIZE 8
#define N 3

int* binaryFile; 
typedef unsigned char BYTE;


void to_binary(int value, char* numOut)
{  
    for (int i = SIZE - 1; i >= 0; --i, value >>= 1)
       	numOut[i] = (value & 1) + '0';
}

long lenFile(FILE* file) {
	fseek(file, 0, SEEK_END);  
	long size = ftell(file);
	fseek(file, 0L, SEEK_SET);
	return size;
}

void to_array(FILE* write_ptr, char arrayFile[]) {
	int position = 0;
	char c;
	while(position != lenFile(write_ptr)) {
		arrayFile[position] = c;  
		position++;
	}  
}

int to_decimal(char numIn[]) {
	int i = 0, dec = 0;
	while (i != SIZE) {  
		if (numIn[i] == '1') 
			dec = dec * 2 + 1; 
		else if (numIn[i] == '0') 
			dec *= 2; 
		i++;
	} 
	return dec;
}

int change(char channelBit[], char file[]) { 
	static int index = 0;
	for (int i = 0; i < N; ++i)
	{ 
		char bit = file[index];   
		index++;
		channelBit[(SIZE - 1) - i] = bit;
	} 
	return 0;
}


int stegnografia(IplImage* img, char file[]) {  
	static int index = 0; 
	int height     = img->height;
	int width      = img->width;
 	char channelBit[SIZE - 1]; 

	for (int i = 0; i < height && index < strlen(file); ++i) {
		uchar* ptr = (uchar*) (img->imageData + i * img->widthStep);
		
		for (int j = 0; j < width && index < strlen(file); ++j)
		{  	
			to_binary(ptr[3 * j + 0], channelBit);  
			change(channelBit, file); 
			ptr[3 * j + 0] = to_decimal(channelBit);

			to_binary(ptr[3 * j + 1], channelBit);  
			change(channelBit, file); 
			ptr[3 * j + 1] = to_decimal(channelBit);

			to_binary(ptr[3 * j + 2], channelBit);  
			change(channelBit, file); 
			ptr[3 * j + 2] = to_decimal(channelBit);
		}
	} 
	
	cvNamedWindow("stegnografia:", CV_WINDOW_AUTOSIZE);
	cvShowImage("stegnografia:", img);
	cvWaitKey(0);
	cvDestroyWindow("stegnografia:");
	cvReleaseImage(&img); 
	
	return 0;
} 

int main(int argc, char** argv)
{ 
	IplImage* image = cvLoadImage("../resources/street.jpg", 1); 
	static int index = 0;

	FILE *write_ptr; 
	char *buffer;

	write_ptr = fopen("../resources/byte.txt","rb");  
	long sizeofFile = lenFile(write_ptr);

	if (write_ptr == NULL) perror ("Error opening file"); 

	buffer = (char *)malloc((sizeofFile+1)*sizeof(char)); // Enough memory for file + \0
	fread(buffer, sizeofFile, 1, write_ptr); // Read in the entire file
	fclose(write_ptr); // Close the file

	char channelBit[(SIZE - 1) * sizeofFile]; 
	for (int i = 0; i < sizeofFile; ++i)
	{
		to_binary(buffer[i], &channelBit[SIZE * i]);
		
	}

	printf("%s\n", channelBit);


	//stegnografia(image, arrayFile);
	return 0;
}