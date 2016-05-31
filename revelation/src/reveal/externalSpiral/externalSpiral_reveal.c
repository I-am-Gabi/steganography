//
// Created by Gabriela on 23/11/15.
//

#include "../../../includes/externalSpiral.h"
#include "../../../includes/log.h"

int initialY, maxY;
int initialX, maxX;
int x = 0, minX = 0;
int y = 0, minY = 0;

int readInLine = 1;
int add = 1;
int firstRun = 1;

/**
 * order arg:
 * 	- 0: Blue
 * 	- 1: Green
 * 	- 2: Red
 * 	- 3: Alpha
 */
int revealSpiralExternal(IplImage *img, char* pathOut, int nBitToRead, int* bit_current, FILE *arq, int channel, int nChannels, char* magic, int* ptr_cont, uchar* ptr_byte) {
    Log("-- stenography in progress --");

    int height     = img->height;
    int width      = img->width;
    int widthStep = img->widthStep;

    int size_msg = 5000;
    uchar* ptrImg = ( uchar* )img->imageData;
    uchar byte = *ptr_byte;

    int cont = *ptr_cont, resul = 0;
    char msg[size_msg];
    int index_msg = 0;
    int flagBREAK = 0;

    initialX = width;
    initialY = height;
    maxX = initialX;
    maxY = initialY;
    int cont_stop = 0;

    while (flagBREAK == 0 && x < initialX && y < initialY) {
        nextPosition();
        int color = ptrImg[y * widthStep + x * nChannels + channel]; // channel
        for (int id = *bit_current - 1; id >= 0; id--) {
            resul = getBit(color, id); // return the bit in the position 0
            byte = setBit(byte, cont, resul); // set the value of result in byte in position cont
            cont--;
            if (cont < 0) {
                if (strstr(msg, magic) != 0) {
                    flagBREAK = 1;
                    break;
                }
                msg[index_msg] = byte;
                index_msg++;
                if (index_msg == size_msg) {
                    fwrite(msg, sizeof(char), sizeof(msg), arq);
                    memset(&msg[0], 0, sizeof(msg));
                    index_msg = 0;
                }
                byte = 0;
                cont = 7;
            }
        }
        cont_stop++;
        if (flagBREAK) {
            break;
        }
    }


    if (flagBREAK)
        msg[strlen(msg) - strlen(magic)] = '\0';
    else {
        *ptr_cont = cont;
        *ptr_byte = byte;
    }

    fwrite(msg, sizeof(char), strlen(msg) * sizeof(char), arq);
    Log("-- stenography finish spiral --");
    return flagBREAK;
}


int nextPosition() {
    if (firstRun) {
        firstRun = 0;
    } else if (readInLine && add) {
        x += 1;
        if (x == maxX - 1) {
            minY += 1;
            readInLine = 0;
        }
    } else if (add && !readInLine) {
        y += 1;
        if (y == maxY - 1) {
            maxX -= 1;
            readInLine = 1;
            add = 0;
        }
    } else if (!add && readInLine) {
        x -= 1;
        if (x == minX) {
            readInLine = 0;
            maxY -= 1;
        }
    } else if (!add && !readInLine) {
        y -= 1;
        if (y == minY) {
            readInLine = 1;
            add = 1;
            minX += 1;
        }
    }
}