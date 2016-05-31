#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "decompress_module.h"
#include "../../includes/binary.h"

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
        printf("%i ", head->code);
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

    int current_char = getc(pFile);
    int compressed_size = 0, original_size = 0;
    int nbsymbols = current_char + 1;

    printf("number of symbols: %i \n", nbsymbols);
    compressed_size++;

    dictionary* Dic = NULL;

    for(int index = 0; index < nbsymbols; ++index) {
        char character = getc(pFile);
        printf("code ASCII: %c | ", character);

        int code_length = getc(pFile);
        printf("code length: %i | ", code_length);

        current_char = getc(pFile);
        int code_symbol = 0;
        for (int index_byte = 7; index_byte > (7 - code_length); --index_byte) {
            int result = getBit(current_char, index_byte);
            if (result == 0) code_symbol = code_symbol * 2;
            else code_symbol = (code_symbol * 2) + 1;
        }
        printf("code symbol: %i \n", code_symbol);

        compressed_size += 3;
        Dic = addItem(Dic, character, code_symbol, code_length);
    }
    printStack(Dic);

    int nbLastBit = getc(pFile);
    printf("\nnumber of bits used in the last bit: %i\n", nbLastBit);
    compressed_size++;

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
        compressed_size++;
        current_char = next_char;
        next_char = getc(pFile);
    }

    msg[index_msg] = '\0';
    original_size = strlen(msg);
    double space = (1 - ((double)compressed_size/(double)original_size)) * 100;
    int negative_saving = ((space) < 0)?1:0;

    printf("compressed size: %d \n"
                   "original_size: %d \n"
                   "msg: %s\n"
                   "space saved: %f\n"
                   "negative saving (1: Yes | 0: Not): %d\n",
           compressed_size, original_size, msg, space, negative_saving);
    fclose(pFile);

    return 0;
}