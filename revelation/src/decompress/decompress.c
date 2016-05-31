#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/decompress.h"
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
        printf("%i \n", head->code);
        puts("---------------------");
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

int readFile(char* filename)
{
    FILE *fileptr;
    char *buffer;
    long filelen;

    fileptr = fopen(filename, "rb");  // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(fileptr);             // Get the current byte offset in the file
    rewind(fileptr);                      // Jump back to the beginning of the file

    buffer = (char *)malloc((filelen+1)*sizeof(char)); // Enough memory for file + \0
    fread(buffer, filelen, 1, fileptr); // Read in the entire file
    fclose(fileptr); // Close the file

    return filelen;
}

// make the decompress
int decompress(char* filename) {
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
    --len_file;
    int nbsymbols = current_char + 1;

    int character = getc(pFile);
    --len_file;
    dictionary *Dic = NULL;
    uchar symbol = malloc(sizeof(uchar) * 8);
    uchar length = malloc(sizeof(uchar) * 8);
    int code = 0;

    for (int index = 0; index < nbsymbols; ++index) {
        for (int index_data = 0; index_data < 3; ++index_data) {
            if (index_data == 0) {
                symbol = character;
                character = getc(pFile);
                --len_file;
            } else if (index_data == 1) {
                length = character;
                character = getc(pFile);
                --len_file;
            } else if (index_data == 2) {
                uchar code_symbol[length];
                for (int cont_bit = (length - 1), index_in_byte = 7; cont_bit >= 0; --cont_bit) {
                    int bit = getBit(character, index_in_byte--);
                    code_symbol[cont_bit] = bit;
                    if (index_in_byte == -1) {
                        character = getc(pFile);
                        --len_file;
                        index_in_byte = 7;
                    }
                }
                if (length % 8 != 0) {
                    character = getc(pFile);
                    --len_file;
                }

                code = 0;
                for (int i = length - 1; i >= 0; --i) {
                    if (code_symbol[i] == 0) code = code * 2;
                    else code = code * 2 + 1;
                }
            }
        }
        Dic = addItem(Dic, symbol, code, length);
    }

    uchar nbLastBit = malloc(sizeof(uchar) * 8);

    for (int cont_bit = 7; cont_bit >= 0; --cont_bit) {
        int bit = getBit(character, cont_bit);
        nbLastBit = setBit(nbLastBit, cont_bit, bit);
    }

    int length_code = 1, buffer = 0;
    int size_temporary = 1000;
    char msg[size_temporary];
    int index_msg = 0;

    current_char = getc(pFile);
    --len_file;
    int next_char = getc(pFile);
    --len_file;
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