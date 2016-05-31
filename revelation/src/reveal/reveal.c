#include <sys/fcntl.h>
#include "../../includes/reveal.h"
#include "../../includes/log.h"

/**
 * order arg:
 * 	- 2: Red
 * 	- 1: Green
 * 	- 0: Blue
 * 	- 4: Alpha
 */
int stenography(IplImage* img, char* pathOut, int nBitToRead, char* orderArg, char* magic, char* hidePattern) {
	FILE *arq;
<<<<<<< HEAD
	arq=open("../resource/TEST/msg.txt", O_RDONLY | O_WRONLY | O_TRUNC);

	puts("-- stenography started --");

	int ptr_cont = 7;
	uchar ptr_byte = 0;
	int ptr_nbBit = nBitToRead;

	if (strlen(orderArg) == 1 && strcasecmp(&orderArg[0], "gray") == 0)
		revealDirect(img, &ptr_nbBit, arq, 0, 1, &ptr_cont, &ptr_byte);

	if (strlen(orderArg) == 1 && strcasecmp(&orderArg[0], "gray") != 0) {
		revealDirect(img, &ptr_nbBit, arq, atoi(&orderArg[0]), img->nChannels, &ptr_cont, &ptr_byte);
	}

	if (strlen(orderArg) == 2) {
		if (revealDirect(img, &ptr_nbBit, arq, atoi(&orderArg[0]), img->nChannels, &ptr_cont, &ptr_byte) == 0)
			revealDirect(img, &ptr_nbBit, arq, atoi(&orderArg[1]), img->nChannels, &ptr_cont, &ptr_byte);
	}

	if (strlen(orderArg) == 3) {
		if (revealDirect(img, &ptr_nbBit, arq, atoi(&orderArg[0]), img->nChannels, &ptr_cont, &ptr_byte) == 0) {
			if (revealDirect(img, &ptr_nbBit, arq, atoi(&orderArg[1]), img->nChannels, &ptr_cont, &ptr_byte) == 0)
				revealDirect(img, &ptr_nbBit, arq, atoi(&orderArg[2]), img->nChannels, &ptr_cont, &ptr_byte);
=======
	fclose(fopen(pathOut, "w"));

	Log("-- stenography started --");

	arq = fopen(pathOut, "ab");
	if(!arq) {
		LogErr("error file");
		exit(EXIT_FAILURE);
	}

	int ptr_cont = 7;
	uchar ptr_byte = 0;
	int ptr_nbBit = nBitToRead;
	int flag_continue = 0;

	if (strcmp(hidePattern, "direct") == 0) {
		if (strlen(orderArg) == 1 && strcasecmp(&orderArg[0], "4") == 0) {
			revealDirect(img, pathOut, nBitToRead, &ptr_nbBit, arq, 0, 1, magic, &ptr_cont, &ptr_byte);
			return 0;
		}

		for (int i = strlen(orderArg), index = 0; i > 0 && flag_continue == 0; --i, index++) {
			char char_channel = orderArg[index];
			int index_channel = atoi(&char_channel);
			flag_continue = revealDirect(img, pathOut, nBitToRead, &ptr_nbBit, arq, index_channel, img->nChannels, magic, &ptr_cont, &ptr_byte);
		}
	} else if (strcmp(hidePattern, "reverse") == 0) {
		if (strlen(orderArg) == 1 && strcasecmp(&orderArg[0], "4") == 0) {
			revealReverse(img, pathOut, nBitToRead, &ptr_nbBit, arq, 0, 1, magic, &ptr_cont, &ptr_byte);
			return 0;
		}

		for (int i = strlen(orderArg), index = 0; i > 0 && flag_continue == 0; --i, index++) {
			char char_channel = orderArg[index];
			int index_channel = atoi(&char_channel);
			flag_continue = revealReverse(img, pathOut, nBitToRead, &ptr_nbBit, arq, index_channel, img->nChannels, magic, &ptr_cont, &ptr_byte);
		}
	} else if (strcmp(hidePattern, "external_spiral") == 0) {
		if (strlen(orderArg) == 1 && strcasecmp(&orderArg[0], "4") == 0) {
			revealSpiralExternal(img, pathOut, nBitToRead, &ptr_nbBit, arq, 0, 1, magic, &ptr_cont, &ptr_byte);
			return 0;
		}

		for (int i = strlen(orderArg), index = 0; i > 0 && flag_continue == 0; --i, index++) {
			char char_channel = orderArg[index];
			int index_channel = atoi(&char_channel); 
			flag_continue = revealSpiralExternal(img, pathOut, nBitToRead, &ptr_nbBit, arq, index_channel, img->nChannels, magic, &ptr_cont, &ptr_byte);
		}
	} else if (strcmp(hidePattern, "internal_spiral") == 0) {
		if (strlen(orderArg) == 1 && strcasecmp(&orderArg[0], "4") == 0) {
			revealSpiralInternal(img, pathOut, nBitToRead, &ptr_nbBit, arq, 0, 1, magic, &ptr_cont, &ptr_byte);
			return 0;
		}

		for (int i = strlen(orderArg), index = 0; i > 0 && flag_continue == 0; --i, index++) {
			char char_channel = orderArg[index];
			int index_channel = atoi(&char_channel); 
			flag_continue = revealSpiralInternal(img, pathOut, nBitToRead, &ptr_nbBit, arq, index_channel, img->nChannels, magic, &ptr_cont, &ptr_byte);
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
		}
	}
	fclose(arq);
	return 0;
} 