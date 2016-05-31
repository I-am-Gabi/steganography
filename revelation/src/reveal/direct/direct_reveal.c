//
// Created by Gabriela on 23/11/15.
//

#include "../../../includes/direct_reveal.h"
<<<<<<< HEAD
=======
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
    arq = fopen("../resource/TEST/msg.txt", "ab");

    if(!arq)
        puts("error file");
=======

int revealDirect(IplImage *img, char* pathOut, int nBitToRead, int* bit_current, FILE *arq, int channel, int nChannels, char* magic, int* ptr_cont, uchar* ptr_byte) {
    Log("-- stenography in progress --");
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c

    int height     = img->height;
    int width      = img->width;
    int widthStep = img->widthStep;

    int size_msg = 5000;
    uchar* ptrImg = ( uchar* )img->imageData;
    uchar byte = *ptr_byte;
<<<<<<< HEAD
    int cont = *ptr_cont, resul = 0;

    char* help = "HELP";
    char msg[50000];
    int c = 0;
=======

    int cont = *ptr_cont, resul = 0;
    char msg[size_msg];
    int index_msg = 0;
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
    int flagBREAK = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j)
        {
<<<<<<< HEAD
            int color = ptrImg[i * img->widthStep + j * nChannels + channel]; // channel
            for (int id = *nBitToRead - 1; id >= 0; id--) {
=======
            int color = ptrImg[i * widthStep + j * nChannels + channel]; // channel
            for (int id = *bit_current - 1; id >= 0; id--) {
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
                resul = getBit(color, id); // return the bit in the position 0
                byte = setBit(byte, cont, resul); // set the value of result in byte in position cont
                cont--;
                if (cont < 0) {
                    int found_magic = 1, k = 1;
                    if (byte == magic[strlen(magic) - 1]) {
                        for (; k < (strlen(magic)); ++k) {
                            if (msg[index_msg - k] != magic[strlen(magic) - (k+1)]) {
                                found_magic = 0;
                            }
                        }

                        if (found_magic) {
                            fwrite(msg, sizeof(char), sizeof(char) * (index_msg - k), arq);
                            flagBREAK = 1;
                            break;
                        }

                    }

                    if (strstr(msg, magic) != NULL) {
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
            if (flagBREAK) break;
        }
        if (i == 0)
            *bit_current = nBitToRead;
        if (flagBREAK)
            break;
    }
<<<<<<< HEAD
    if (flagBREAK)
        msg[strlen(msg) - strlen(help)] = '\0';
    else {
        *ptr_cont = cont;
        *ptr_byte = byte;
    }

    fwrite(msg, sizeof(char), strlen(msg) * sizeof(char), arq);
    puts("-- stenography finish [direct] --");
    //printf("\n%s\n", msg);
=======

    if (!flagBREAK) {
        *ptr_cont = cont;
        *ptr_byte = byte;
    }
    //fwrite(msg, sizeof(char), strlen(msg) * sizeof(char), arq);
    Log("-- stenography finish direct --");
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
    return flagBREAK;
}