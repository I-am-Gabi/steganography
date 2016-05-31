//
// Created by Gabriela on 23/11/15.
//

<<<<<<< HEAD
#include "direct_reveal.h"
=======
#include "../../../includes/reverse_reveal.h"
#include "../../../includes/log.h"
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c

/**
 * order arg:
 * 	- 0: Blue
 * 	- 1: Green
 * 	- 2: Red
 * 	- 3: Alpha
 */
<<<<<<< HEAD
int revealDirect(IplImage *img, int* nBitToRead, FILE *arq, int channel, int nChannels, int* ptr_cont, uchar* ptr_byte) {
    puts("-- stegnography in progress --");
    arq = fopen("../resource/TEST/msg.txt", "wb");
    if(!arq)
        puts("error file");

    int height     = img->height;
    int width      = img->width;

    uchar* ptrImg = ( uchar* )img->imageData;
    uchar byte = *ptr_byte;
    int cont = *ptr_cont, resul = 0;

    char* help = "HELP";
    char msg[5000];
    int c = 0;
    int flagBREAK = 0;

    for (int i = height; i > 0; ++i) {
        for (int j = width; j > 0; ++j)
        {
            int color = ptrImg[i * img->widthStep + j * nChannels + channel]; // channel
            for (int id = *nBitToRead - 1; id >= 0; id--) {
=======
int revealReverse(IplImage *img, char* pathOut, int nBitToRead, int* bit_current, FILE *arq, int channel, int nChannels, char* magic, int* ptr_cont, uchar* ptr_byte) {
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

    for (int i = height - 1; i >= 0; --i) {
        for (int j = width - 1; j >= 0; --j)
        {
            int color = ptrImg[i * widthStep + j * nChannels + channel]; // channel
            for (int id = *bit_current - 1; id >= 0; id--) {
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
                resul = getBit(color, id); // return the bit in the position 0
                byte = setBit(byte, cont, resul); // set the value of result in byte in position cont
                cont--;
                if (cont < 0) {
<<<<<<< HEAD
                    if (strstr(msg, help) != 0) {
                        flagBREAK = 1;
                        break;
                    }
                    msg[c] = byte;
                    c++;
=======
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
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
                    byte = 0;
                    cont = 7;
                }
            }
        }
<<<<<<< HEAD
        if (flagBREAK)
            break;
    }
    if (flagBREAK)
        msg[strlen(msg) - strlen(help)] = '\0';

    fwrite(msg, sizeof(char), strlen(msg) * sizeof(char), arq);
    puts("-- stegnography finish direct --");
    printf("\n%s\n", msg);
=======
        if (i == 0)
            *bit_current = nBitToRead;
        if (flagBREAK)
            break;
    }

    if (flagBREAK)
        *strstr(msg, magic) = '\0';
    else {
        *ptr_cont = cont;
        *ptr_byte = byte;
    }

    fwrite(msg, sizeof(char), strlen(msg) * sizeof(char), arq);
    Log("-- stenography finish reverse --");
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
    return flagBREAK;
}
