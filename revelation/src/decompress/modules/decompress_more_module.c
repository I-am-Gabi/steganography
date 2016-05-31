#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "decompress_more_module.h"
#include "../../../includes/binary.h"

// add item in the dictionary
dictionary* addItem(dictionary* Dic, char c, int code, int code_length) {
    dictionary* dic_update = malloc(sizeof(dictionary));
    dic_update->next = Dic;
    dic_update->character = c;
    dic_update->code = code;
    dic_update->code_length = code_length;
    return dic_update;
}

// print stack
void printStack(dictionary* head) {
    if (head->next == NULL) {
        printf("%c:", head->character);
        printf("%i \n", head->code);
    } else {
        printf("%c:", head->character);
        printf("%i ", head->code);
        printStack(head->next);
    }
}

// get the character with a specific code
char getCode(dictionary* head, int length, int code) {
    if (head->next == NULL) {
        if (head->code_length == length && head->code == code)
            return head->character;
        return NULL;
    } else {
        if (head->code_length == length && head->code == code)
            return head->character;
        return getCode(head->next, length, code);
    }
}

// make the decompress
int decompress(char* filename) {
    FILE * pFile;
    pFile = fopen(filename, "r");
    if (pFile == NULL) {
        puts("FILE ERROR");
        exit(EXIT_FAILURE);
    }

    char current_char = getc(pFile);
    int compressed_size = 0, original_size = 0;
    int nbsymbols = current_char + 1;

    int characters[nbsymbols];
    for(int index = 0; index < nbsymbols; ++index)
        characters[index] = getc(pFile);

    int shape = getc(pFile);
    dictionary* Dic = NULL;
    Dic = getCodes(shape, characters);

    int nbLastBit = 8;
    printf("\nnumber of bits used in the last bit: %i\n", nbLastBit);

    int length = 1;
    int buffer = 0;
    char* msg = malloc(sizeof(char) * 10);
    int index_msg = 0;

    current_char = getc(pFile);
    int next_char = getc(pFile);

    int index_stop = 0;
    while(current_char != EOF) {
        if (next_char == EOF)
            index_stop = 8 - nbLastBit;
        for (int index = 7; index >= index_stop; --index, ++length)
        {
            int bit = getBit(current_char, index);
            if (bit == 0) buffer *= 2;
            else buffer = (buffer * 2) + 1;
            char code = getCode(Dic, length, buffer);
            if (code != NULL) {
                msg[index_msg] = code;
                index_msg++;
                length = 0;
                buffer = 0;
            }
        }
        current_char = next_char;
        next_char = getc(pFile);
    }

    msg[index_msg] = '\0';

    printf("msg: %s\n", msg);
    fclose(pFile);

    return 0;
}

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