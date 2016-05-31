//
// Created by Gabriela on 23/11/15.
//

#include "../../includes/binary.h"

// pronto the bit
void printToBit(int number, int base) {
    if (number/base)
        printToBit(number / base, base);
    putchar ((number % base) + ((number % base > 9) ? ('A' - 10) : '0'));
}

// return one bit in a position
int getBit(uchar byte, int pos) {
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