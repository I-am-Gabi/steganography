//
// Created by Gabriela on 23/11/15.
//

#include "../../../includes/internalSpiral.h"
#include "../../../includes/log.h"

int maxY;
int maxX;
int xP = 0;
int yP = 0;
int contMoviment = 0;
int bitRatio = 1, starte = 1;
int InLine = 0;
int addPosition = 0;

/**
 * order arg:
 * 	- 0: Blue
 * 	- 1: Green
 * 	- 2: Red
 * 	- 3: Alpha
 */
int revealSpiralInternal(IplImage *img, char* pathOut, int nBitToRead, int* bit_current, FILE *arq, int channel, int nChannels, char* magic, int* ptr_cont, uchar* ptr_byte) {
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

    maxX = width;
    maxY = height;
    xP = maxX/2;
    yP = maxY/2;
    int cont_stop = 0;

    while (flagBREAK == 0 && (xP < maxX && xP >= 0) && (yP < maxY && yP >= 0)) {
        nextPositionInternal();
        int color = ptrImg[yP * widthStep + xP * nChannels + channel]; // channel
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
        if (cont_stop == 1000 || flagBREAK) {
            flagBREAK = 1;
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


int nextPositionInternal() {
    if (starte == 1) {
        starte = 0;
    } else if (!InLine && !addPosition) {
        yP -= 1;
        contMoviment += 1;
        if (contMoviment == bitRatio) {
            contMoviment = 0;
            addPosition = 1;
            InLine = 1;
        }
    } else if (addPosition && InLine) {
        xP += 1;
        contMoviment += 1;
        if (contMoviment == bitRatio) {
            contMoviment = 0;
            InLine = 0;
            bitRatio += 1;
        }
    } else if (addPosition && !InLine) {
        yP += 1;
        contMoviment += 1;
        if (contMoviment == bitRatio) {
            contMoviment = 0;
            addPosition = 0;
            InLine = 1;
        }
    } else if (!addPosition && InLine) {
        xP -= 1;
        contMoviment += 1;
        if (contMoviment == bitRatio)
        {
            bitRatio += 1;
            contMoviment = 0;
            InLine = 0;
        }
    }
}