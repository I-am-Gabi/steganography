#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_ 

#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <magic.h>

int check_imageSignature(char* filename, char** format);

int check_pathImageIn(char* filename);

int check_pathImageOut(const char* filename);

int check_bitFactor(int bitFactor, int depth);

int check_hidePattern(char* pattern);

int check_channels(char* str, int channels, char* filename);

void order(char* pathIn, char* orderArg);

#endif