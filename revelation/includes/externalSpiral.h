//
// Created by Gabriela on 09/01/16.
//

#ifndef PROTOTYPE_EXTERNALSPIRAL_H
#define PROTOTYPE_EXTERNALSPIRAL_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <stdint.h>
#include <wchar.h>

#include <stdio.h>
#include "binary.h"


int revealSpiralExternal(IplImage *img, char* pathOut, int nBitToRead, int* bit_current, FILE *arq, int channel, int nChannels, char* magic, int* ptr_cont, uchar* ptr_byte);

int nextPosition();
#endif //PROTOTYPE_EXTERNALSPIRAL_H
