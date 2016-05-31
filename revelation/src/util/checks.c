#include "../../includes/arguments.h"
#include "../../includes/log.h"

/**************************************************
 *  Module with methods responsibles for checking
 *  the validity of the arguments received by the
 *  interface.
 *  Author: Gabriela Cavalcante
 **************************************************/

/**
 * Method to check the image signature and analyze the file contents.
 * arg: char* filename Path to image.
 * return: 0 to error and 1 to valid argument.
 *
 * PNG (portable network graphics) = PNG image data, 640 x 480, 8-bit/color RGB, non-interlaced
 * BMP (bitmap image) = PC bitmap, Windows 3.x format, 800 x 600 x 24
 * PPM (portable pixmap format) = Netpbm image data, size = 512 x 512, pixmap, ASCII text
 * PGM (portable graymap format) = Netpbm image data, size = 24 x 7, greymap, ASCII text
 *
 * Then, if the image is PNG we can find 'PNG' in the image signature,
 * if it's BMP, we can find 'bitmap', if it's PPM there are 'pixmap',
 * and if it's PGM there are greymap in the image signature.
 */
int check_imageSignature(char* filename, char** format) {
    magic_t handle = magic_open(MAGIC_NONE|MAGIC_COMPRESS);
    magic_load(handle, NULL);
    const char * type = magic_file(handle, filename);
    magic_close(handle);

    if (type) {
<<<<<<< HEAD
        if(strstr(type, "PNG") != NULL) {
            *format = "png";
            return EXIT_SUCCESS;
        }
        else if(strstr(type, "bitmap") != NULL) {
            *format = "bmp";
            return EXIT_SUCCESS;
        }
        else if(strstr(type, "pixmap") != NULL) {
            *format = "pmp";
            return EXIT_SUCCESS;
        }
        else if(strstr(type, "greymap") != NULL) {
            *format = "greymap";
            return EXIT_SUCCESS;
        }
        else
            return EXIT_FAILURE;
    }

    return EXIT_FAILURE;
=======
        if (strstr(type, "PNG") != NULL) {
            *format = "png";
            return EXIT_SUCCESS;
        } else if (strstr(type, "bitmap") != NULL) {
            *format = "bmp";
            return EXIT_SUCCESS;
        } else if (strstr(type, "greymap") != NULL) {
            *format = "pgm";
            return EXIT_SUCCESS;
        } else if (strstr(type, "pgm") != NULL) {
            *format = "pgm";
            return EXIT_SUCCESS;
        } else if (strstr(type, "ppm") != NULL) {
            *format = "ppm";
            return EXIT_SUCCESS;
        } else {
            LogErr("error file signature");
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
}

/**
 * Method to check if the image path input is valid (if the image exists).
 * arg: char* filename Path to image.
 * return: 0 to error and 1 to valid argument.
 */
int check_pathImageIn(char* filename) {
    struct stat buf;
    malloc(sizeof(struct stat));
    if (stat(filename, &buf) == 0) return EXIT_SUCCESS;
    LogErr("error file path in");
    return EXIT_FAILURE;
}

/**
 * Method to check if the image path to output is valid (if the path exists).
 * arg: char* filename Path to image.
 * return: 0 to error and 1 to valid argument.
 */
int check_pathImageOut(const char* filename) {
    FILE *fptr;
    fptr = fopen(filename, "rb+");
    if(fptr == NULL) { //if file does not exist, create it
        fptr = fopen(filename, "wb");
        if (fptr == NULL) {
            LogErr("error path out");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * Method to check if the bit factor is valid.
 * arg: char* filename Path to image.
 * 		int   depth	   The depth bit number (eg: 8 bits)
 * return: 0 to error and 1 to valid argument.
 */
int check_bitFactor(int bitFactor, int depth) {
    if (bitFactor > depth) {
        LogErr("error bit factory greater than the threshold");
        return EXIT_FAILURE;
    }
    if (bitFactor <= 0) {
        LogErr("error bit factory negative");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * Method to check the hide pattern give us by the User.
 * arg: char* pattern Hide pattern informed by User.
 * return: 0 to error and 1 to valid argument.
 */
int check_hidePattern(char* pattern) {
    if(strcasecmp(pattern, "direct") == 0)
        return EXIT_SUCCESS;
    else if(strcasecmp(pattern, "reverse") == 0)
        return EXIT_SUCCESS;
    else if(strcasecmp(pattern, "external_spiral") == 0)
        return EXIT_SUCCESS;
    else if(strcasecmp(pattern, "internal_spiral") == 0)
        return EXIT_SUCCESS;
    LogErr("error pattern does not exist");
    return EXIT_FAILURE;
}

/**
 * Method to check the if the channels give us by the User are valid.
 * If the image has just one channel, it has just one channel.
 * If the image is a colored image, it can be RGB or RGBA.
 * arg: char* str Channel informed by the User
 * 		int   channels The number of image channels
 * 		char* filename Image path
 * return: 0 to error and 1 to valid argument.
 */
int check_channels(char* chan, int channels, char* filename) {
    char str[strlen(chan) + 1];
    strcpy(str, chan);
    str[strlen(str)] = '\0';
    
    if (channels == 1) {
        if (strcasecmp(str, "gray") != 0) {
            LogErr("channel inconsistent");
            return EXIT_FAILURE;
        } else return EXIT_SUCCESS;
    }
    
    magic_t handle = magic_open(MAGIC_NONE|MAGIC_COMPRESS);
    magic_load(handle, NULL);
    const char * type = magic_file(handle, filename);
    
    int flag = 0;
    if (strstr(type, "RGBA") != NULL)
        flag = 1;
    else if (strstr(type, "RGB") != NULL)
        flag = 2;
    
    char* pch;
    pch = strtok(str," , ");
    
    while (pch != NULL)
    {
        if (!((strcasecmp(pch, "red") == 0)   ||
                (strcasecmp(pch, "green") == 0) ||
                (strcasecmp(pch, "blue") == 0)  ||
                ((strcasecmp(pch, "alpha") == 0) && flag == 1))) {
            LogErr("channel inconsistent");
            return EXIT_FAILURE;
        }
        pch = strtok (NULL, " , ");
    }
    return EXIT_SUCCESS;
}

/**
 * order arg:
 * 	- 0: blue
 * 	- 1: green
 * 	- 2: red
 * 	- 3: alpha
 */
void order(char* channels, char* orderArg) {
    char* pch;
	pch = strtok(channels, " , ");

	int index = 0;

	while (pch != NULL) {
		if (strcasecmp(pch, "blue") == 0)
			orderArg[index] = '0';
		else if (strcasecmp(pch, "green") == 0)
			orderArg[index] = '1';
		else if (strcasecmp(pch, "red") == 0)
			orderArg[index] = '2';
		else if (strcasecmp(pch, "alpha") == 0)
			orderArg[index] = '3';
		else
			orderArg[index] = '\0';
		index++;
		pch = strtok (NULL, " , ");
	}
}