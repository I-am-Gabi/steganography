//
// Created by Gabriela on 09/01/16.
//

#ifndef PROTOTYPE_INTERNALSPIRAL_H
#define PROTOTYPE_INTERNALSPIRAL_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <stdint.h>
#include <wchar.h>

#include <stdio.h>
#include "binary.h"

int revealSpiralInternal(IplImage *img, char* pathOut, int nBitToRead, int* bit_current, FILE *arq, int channel, int nChannels, char* magic, int* ptr_cont, uchar* ptr_byte);

int nextPositionInternal();

#endif //PROTOTYPE_EXTERNALSPIRAL_H
