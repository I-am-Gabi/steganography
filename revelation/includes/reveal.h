#ifndef _REVEAL_H_
#define _REVEAL_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <unistd.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "direct_reveal.h"
<<<<<<< HEAD
=======
#include "reverse_reveal.h"
#include "externalSpiral.h"
#include "internalSpiral.h"
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c

int stenography(IplImage* img, char* pathOut, int bit, char* orderArg, char* magic, char* hidePattern);

#endif