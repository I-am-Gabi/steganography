//Mathieu Mérino
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printByte(char byte){
    char nb[9];
    for (int i = 8; i > 0; --i){
        if (byte % 2 == 0) nb[i - 1] = '0';
        else nb[i - 1] = '1';
        byte = byte >> 1;
    }
    nb[8] = '\0';
    printf("%s\n", nb);
}
void printTab(int width, int height, unsigned char tab[width][height]){
    for (int x = 0; x < width; ++x){
        for (int y = 0; y < height; ++y){
            printf("%d \t", tab[x][y]);
        }
        printf("\n");
    }
}
unsigned char encodeByte(char byte, char message, unsigned nbBits){
    unsigned int bits[nbBits];
    for (unsigned i = 0; i < nbBits; ++i) {
        bits[i] = message % 2;
        message = message >> 1;
        byte = byte >> 1;
    }
    for (int i = nbBits - 1; i >= 0; --i){
        byte = byte << 1;
        byte += bits[i];
    }
    return byte;
}
unsigned char decodeByte(unsigned char byte, unsigned nbBits){
    unsigned char message = 0;
    while (nbBits > 0){
        if (byte % 2 == 1)
            message += 1;
        message = message << 1;
        byte = byte >> 1;
        --nbBits;
    }
    message = message >> 1;
    return message;
}
void createFakeImage(int width, int height, unsigned char tab [width][height]){
    srand(time(NULL));
    for (unsigned x = 0; x < width; ++x){
        for (unsigned y = 0; y < height; ++y){
            tab[x][y] = rand() % 256;
        }
    }
}
void test2(char* fileName){
    unsigned width = 10, height = 10, encodeBits = 2;
    FILE* file = fopen(fileName, "r");
    unsigned char tab[width][height];
    createFakeImage(width, height, tab);
    printTab(width, height, tab);
    int c, x = 0, y = 0, compteur = 0;
    while((c = getc(file)) != EOF){
        int bitsEncoded = 0;
        while (bitsEncoded < 8){
            tab[x][y] = encodeByte(tab[x][y], c, encodeBits);
            c >> encodeBits;
            bitsEncoded += encodeBits;
            if (++x == width){
                x = 0;
                ++y;
            }
        }
        ++compteur;
    }
    printf("\n\n");
    printTab(width, height, tab);
    //Décodage
    char msg[compteur];
    x = 0;
    y = 0;
    while (compteur > 0){

        c = 0;
        int bitsDecoded = 0;
        while (bitsDecoded < 8){
            c += decodeByte(tab[x][y], encodeBits);
            c << 2;
            bitsDecoded += 2;
            if (++x == width){
                x = 0;
                ++y;
            }
        }
        msg[compteur - 1] = (char) c;
        printf("%c", c);
        --compteur;
    }
}
void test1(){
    unsigned char nb = 227;
    unsigned char message = 13;
    printByte(nb);
    printByte(message);
    nb = encodeByte(nb, message, 4);
    printByte(nb);
    printByte(decodeByte(nb, 4));
}
int main(){
    //test2("E:\\Users\\Mathieu\\Documents\\GitHub\\kgms\\prototype\\c\\resources\\byte.txt");
    test1();
}