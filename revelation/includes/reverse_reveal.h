//
// Created by Gabriela on 23/11/15.
//

#ifndef REVERSE_REVEAL_H
#define REVERSE_REVEAL_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <stdint.h>
#include <wchar.h>

#include <stdio.h>
#include "binary.h"

int revealReverse(IplImage *img, char* pathOut, int nBitToRead, int* bit_current, FILE *arq, int channel, int nChannels, char* magic, int* ptr_cont, uchar* ptr_byte);

#endif //DIRECT_REVEAL_H
