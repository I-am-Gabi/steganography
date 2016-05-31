//
// Created by Gabriela on 23/11/15.
//

#ifndef REVEALONECHANNEL_H
#define REVEALONECHANNEL_H

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <stdio.h>
#include "binary.h"

int revealDirect(IplImage *img, int* nBitToRead, FILE *arq, int channel, int nChannels, int* ptr_cont, uchar* ptr_byte);

#endif //PROTOTYPE_REVEALRGB_H
