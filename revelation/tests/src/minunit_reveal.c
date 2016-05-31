<<<<<<< HEAD
/******************************************************************
 *  Module with Unit Tests.
 *  Author: Gabriela Cavalcante
 ******************************************************************/

=======
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
#include <stdio.h>
#include <opencv2/imgcodecs/imgcodecs_c.h>
<<<<<<< HEAD
=======
#include "../includes/minunit_reveal.h"
#include "../../includes/binary.h"
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c

#include "../includes/minunit_reveal.h"
#include "../../includes/binary.h"

int const CHANNEL_BLUE = 0;
int const CHANNEL_GREEN = 1;
int const CHANNEL_RED = 2;

FILE* openFile(char* filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    return fp;
}

IplImage* createImage(int width, int height, int bits, int channels) {
    IplImage* imgScribble = cvCreateImage(cvSize(width, height), bits, channels);
    return imgScribble;
}

void test_imageRed(FILE *fp, IplImage* imgScribble, int channel, int nbit, char* namefile) {
    int c, resul, bit;
    uchar byte;

    int pos = 7;
    c = getc(fp);

    int height    = imgScribble->height;
    int width     = imgScribble->width;

    uchar* ptrImg = ( uchar* )imgScribble->imageData;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int color = ptrImg[i * imgScribble->widthStep + j * imgScribble->nChannels + channel];

            for (int id = nbit - 1; id >= 0; id--) {
                bit = getBit(c, pos);
                pos--;
                color = setBit(color, id, bit);
                if(pos < 0) {
                    if (c == '\0' || c == EOF) break;
                    c = getc(fp);
                    printf("%c", c);
                    pos = 7;
                }
            }

            ptrImg[i * imgScribble->widthStep + j * imgScribble->nChannels + channel] = color;
        }
        if (c == '\0' || c == EOF) break;
    }
    puts("\n");
    cvSaveImage(namefile, imgScribble, 0);
}

int main() {
    IplImage* imgScribble = createImage(2500, 2500, 8, 3);

<<<<<<< HEAD
    FILE *fp = openFile("../../resource/TEST/txt/3-19disc.txt");
    test_imageRed(fp, imgScribble, CHANNEL_RED, 1, "../resource/TEST/large_680x1024.png");

    /*fp = openFile("../../resource/TEST/test2.txt");
    test_imageRed(fp, imgScribble, CHANNEL_GREEN, 1, "../resource/TEST/test_green_1bit.png");

    fp = openFile("../../resource/TEST/test3.txt");
    test_imageRed(fp, imgScribble, CHANNEL_RED, 1, "../resource/TEST/test_red_1bit.png");

    fp = openFile("../../resource/TEST/test1.txt");
    test_imageRed(fp, imgScribble, CHANNEL_BLUE, 2, "../resource/TEST/test_blue_2bit.png");

    fp = openFile("../../resource/TEST/test2.txt");
    test_imageRed(fp, imgScribble, CHANNEL_GREEN, 2, "../resource/TEST/test_green_2bit.png");

    fp = openFile("../../resource/TEST/test3.txt");
    test_imageRed(fp, imgScribble, CHANNEL_RED, 2, "../resource/TEST/test_red_2bit.png");*/
=======
    FILE *fp = openFile("../../resource/TEST/test1.txt");
    test_imageRed(fp, imgScribble, CHANNEL_BLUE, 1, "../../resource/TEST/WorldMapBig.png");

    fp = openFile("../../resource/TEST/test2.txt");
    test_imageRed(fp, imgScribble, CHANNEL_GREEN, 1, "../../resource/TEST/test_green_1bit.png");

    fp = openFile("../../resource/TEST/test3.txt");
    test_imageRed(fp, imgScribble, CHANNEL_RED, 1, "../../resource/TEST/test_red_1bit.png");

    fp = openFile("../../resource/TEST/test1.txt");
    test_imageRed(fp, imgScribble, CHANNEL_BLUE, 2, "../../resource/TEST/test_blue_2bit.png");

    fp = openFile("../../resource/TEST/test2.txt");
    test_imageRed(fp, imgScribble, CHANNEL_GREEN, 2, "../../resource/TEST/test_green_2bit.png");

    fp = openFile("../../resource/TEST/test3.txt");
    test_imageRed(fp, imgScribble, CHANNEL_RED, 2, "../../resource/TEST/test_red_2bit.png");
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
}