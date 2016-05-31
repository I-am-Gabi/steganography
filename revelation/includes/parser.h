//
<<<<<<< HEAD
// Created by Gabriela on 05/01/16.
//

#ifndef _PARSER_H
#define _PARSER_H

#include <opencv/highgui.h>

int parser(int argc, char *argv[], char** formatImage, char** pathIn, char** pathOut, char** hidePattern, char** channels, int* bitFactor, IplImage** imgIn);

#endif
=======
// Created by Gabriela on 08/01/16.
//

#ifndef PROTOTYPE_PARSER_H
#define PROTOTYPE_PARSER_H

#include <string.h>
#include <opencv/cxcore.h>

int parser(char* formatImage, char* pathIn, char* pathOut, char* channels, char* hidePattern, char* magic, int bitFactor, IplImage* imgIn);

#endif //PROTOTYPE_PARSER_H
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
