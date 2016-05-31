/* DISSIMULATION C */
#include <stdio.h>
#include <opencv/highgui.h>

int const CHANNEL = 1;
int const NBIT = 3;

struct nextStep {
	int byte;
	int pos;
};

// add HELP (magic number) in the file
void addHELP(char* filename) {
	FILE *file = fopen(filename, "a");
	fprintf(file, "%s", "HELP");
	fclose(file);
}

IplImage* readImage(const char* filename) {
	IplImage* img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED);
	return img;
}

// return one bit in a position
int getBit(char byte, int pos) {
	return (((byte >> pos) & 0x01) != 0);
}

// change one bit in a position
uchar setBit(uchar byte, int pos, int val) {
	if(val)
		byte |= (1 << pos);
	else
		byte &= ~(1 << pos);
	return byte;
}

struct nextStep* hide(IplImage* img, FILE* fp, struct nextStep* step) {
	printf(" -- dissimulation in progress --\n");
	int width   = img->width;
	int height 	= img->height;
	char* help = "HELP";

	int flagEnd = 0;
	uchar* ptrImg = ( uchar* )img->imageData;

	int c, bit;

	int pos = step->pos;
	c = step->byte;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int color = ptrImg[i * img->widthStep + j * img->nChannels + CHANNEL];

			for (int id = NBIT - 1; id >= 0; id--) {
				bit = getBit(c, pos);
				pos--;
				color = setBit(color, id, bit);
				if(pos < 0) {
					if (c == '\0') {
						flagEnd = 1;
						break;
					}
					c = getc(fp);
					pos = 7;
				}
			}
			ptrImg[i * img->widthStep + j * img->nChannels + CHANNEL] = color;
		}
		if (c == '\0') break;
	}
	if (flagEnd == 0) {
		step->byte = c;
		step->pos = pos;
		return step;
	}
	else if (flagEnd == 1)
		cvSaveImage("../resource/hide.png", img, 0);
	return NULL;
}

int main ()
{
	printf(" -- dissimulation --\n");

	// message
	FILE *fp;
	fp = fopen("../resource/text.txt", "rb");

	// image to cache the message
	IplImage* img = cvLoadImage("../resource/boneca.png", CV_LOAD_IMAGE_UNCHANGED);


	int ch = getc(fp);

	struct nextStep steg;
	steg.byte = ch;
	steg.pos = 7;

	steg = *(hide(img, fp, &steg));
	if (steg) {
		puts("DONE");
	}
	else {
		printf("%d", steg.byte);
		printf("%d", steg.pos);
	}
	
	return 0;
}