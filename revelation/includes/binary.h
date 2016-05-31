//
// Created by Gabriela on 23/11/15.
//

#ifndef BINARY_H
#define BINARY_H

#include <stdio.h>
#include <opencv/cv.h>

void printToBit(int number, int base);

int getBit(uchar byte, int pos);

uchar setBit(uchar byte, int pos, int val);

#endif //BINARY_H
