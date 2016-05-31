//
// Created by Gabriela on 18/01/16.
//

#ifndef PROTOTYPE_DECOMPRESS_MODULE_H
#define PROTOTYPE_DECOMPRESS_MODULE_H

#include <stdio.h>

typedef struct Item
{
    char character;
    int code;
    int code_length;
    struct Item* next;
} dictionary;

dictionary* addItem(dictionary* Dic, char c, int code, int code_length);

void printStack(dictionary* head);

char getCode(dictionary* head, int length, int code);

int decompress(char* filename);

#endif //PROTOTYPE_DECOMPRESS_H
