#ifndef _VALIDATOR_ARGUMENT_H_
#define _VALIDATOR_ARGUMENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opencv/highgui.h>

#include "arguments.h"

void validPath(char* formatImage, char* pathIn, char* pathOut, IplImage** imgIn);
void validFormatImage(char* formatImage, char* pathIn);
void validBitFactor(int bitFactor, IplImage** imgIn);
void validChannel(char* pathIn, char* channels, IplImage** imgIn);
void validPattern(char* hidePattern);

#endif