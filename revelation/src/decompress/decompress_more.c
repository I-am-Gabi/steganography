#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/decompress.h"
#include "../../includes/decompress_more.h"
#include "../../includes/binary.h"

int toInt(char* string) {
    int code = 0;
    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] == '0') code = code * 2;
        else code = code * 2 + 1;
    }
    return code;
}

dictionary* getCodes(char byte, int* characters) {
    char current_code[100] = {""};
    int before_value = -1;
    char* codes[100];
    int index_codes = 0, index_characters = 0;
    int flag_side = 0;
    strcat(current_code, "0");

    dictionary* Dic = NULL;
    for (int index_bit = 7; index_bit >= 0; --index_bit) {
        int bit = getBit(byte, index_bit);
        if (bit == 0) {
            if (before_value == 1) {
                strcat(current_code, "0");
                codes[index_codes] = current_code;
                Dic = addItem(Dic, characters[index_characters++], toInt(current_code), strlen(current_code));
                ++index_codes;
            } else {
                if (flag_side == 0) {
                    current_code[strlen(current_code) - 1] = '\0';
                    strcat(current_code, "1");
                    codes[index_codes] = current_code;
                    Dic = addItem(Dic, characters[index_characters++], toInt(current_code), strlen(current_code));
                    flag_side = 1;
                } else {
                    current_code[strlen(current_code) - 2] = '\0';
                    strcat(current_code, "1");
                    flag_side = 0;
                    codes[index_codes] = current_code;
                    Dic = addItem(Dic, characters[index_characters++], toInt(current_code), strlen(current_code));
                    ++index_codes;
                }
            }
        } else {
            if (before_value == 1) {
                flag_side = 0;
                flag_side = 0;
                strcat(current_code, "0");
            } else if (before_value == 0) {
                flag_side = 1;
                current_code[strlen(current_code) - 2] = '\0';
                strcat(current_code, "1");
            }
        }
        before_value = bit;
    }
    printStack(Dic);

    return Dic;
}

// make the decompress
int decompress_more(char* filename) {
    int len_file = readFile(filename) + 1;

    FILE *pFile;
    pFile = fopen(filename, "rb");

    FILE *output;
    output = fopen("resource/output/msg_decompress.txt", "w");

    if (pFile == NULL) {
        puts("FILE ERROR");
        exit(EXIT_FAILURE);
    }

    int current_char = getc(pFile);
    int nbsymbols = current_char + 1;

    int characters[nbsymbols];
    for(int index = 0; index < nbsymbols; ++index)
        characters[index] = getc(pFile);

    for (int i = 0; i < nbsymbols; ++i) {
        //printf("%c ", characters[i]);
    }

    int shape = getc(pFile);
    dictionary *Dic = NULL;
    Dic = getCodes(shape, characters);

    printStack(Dic);

    uchar nbLastBit = malloc(sizeof(uchar) * 8);
    int character = getc(pFile);

    for (int cont_bit = 7; cont_bit >= 0; --cont_bit) {
        int bit = getBit(character, cont_bit);
        nbLastBit = setBit(nbLastBit, cont_bit, bit);
    }

    int length_code = 1, buffer = 0;
    int size_temporary = 1000;
    char msg[size_temporary];
    int index_msg = 0;

    current_char = getc(pFile);;
    int next_char = getc(pFile);
    int index_stop = 0;

    while (len_file >= 0) {
        if ((len_file - 1) == 0) {
            index_stop = 8 - nbLastBit;
        }
        for (int index = 7; index >= index_stop; --index, ++length_code) {
            int bit = getBit(current_char, index);
            if (bit == 0) buffer *= 2;
            else buffer = (buffer * 2) + 1;
            char code = getCode(Dic, length_code, buffer);
            if (code != NULL) {
                fputc(code, output);
                length_code = 0;
                buffer = 0;
            }
        }
        current_char = next_char;
        next_char = getc(pFile);
        if (current_char == EOF) {
        }
        --len_file;
    }

    fclose(pFile);
    fclose(output);
    return 0;
}