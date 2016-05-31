#include <unistd.h>
#include <stdlib.h>
<<<<<<< HEAD

#include <opencv/cxcore.h>
#include <getopt.h>

=======
#include <getopt.h>

#include <opencv/cxcore.h>
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
#include "../includes/arguments.h"
#include "../includes/reveal.h"
<<<<<<< HEAD
#include "../includes/image.h"
=======
#include "../includes/log.h"
#include "../includes/parser.h"
#include "../includes/decompress.h"
#include "../includes/decompress_more.h"
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c

char* formatImage = NULL;
char* pathIn = NULL;
char* pathOut = NULL;
char* hidePattern = "direct";
<<<<<<< HEAD
char* channels = NULL;
=======
char* channels = "Red,Green,Blue";
char* magic_number;

IplImage* imgIn = NULL;

>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
int bitFactor = 1;
IplImage* imgIn = NULL;

<<<<<<< HEAD
// if we don't have the image format (User), but
// we have the image path, we can check the file signature
// test if the path to input was given and if the path exists
void validPath() {
    if(!formatImage && (check_imageSignature(pathIn, formatImage) == 0 || check_pathImageIn(pathIn) == 0))
        exit(EXIT_FAILURE);
    else
        imgIn = readImage(pathIn);

    // test if the path to input was given and if the path exists
    if(pathOut && !check_pathImageOut(pathOut))
        exit(EXIT_FAILURE);
}

// if we have the image format give us by the user
// and the image signature, but they aren't equals
// or don't follow the paterns: error
void validFormatImage() {
    if(formatImage && pathIn && (
            (strstr(pathIn, formatImage) == NULL)  ||
            (check_imageSignature(pathIn, &formatImage) == 0)  ||
            (check_pathImageIn(pathIn)    == 0)))
        exit(EXIT_FAILURE);
}

// test if the bit factor is valid
void validBitFactor() {
    if((imgIn) && !check_bitFactor(bitFactor, (imgIn)->depth))
        exit(EXIT_FAILURE);
}

// test if the channels informed by the User are valid
void validChannel() {
    if(channels && pathIn && !check_channels(channels, (imgIn)->nChannels, pathIn))
        exit(EXIT_FAILURE);
}

// test if the hide pattern informed is valid
void validPattern() {
    if(!check_hidePattern(hidePattern))
        exit(EXIT_FAILURE);
}
=======
int fsize(FILE *fp){
	int prev=ftell(fp);
	fseek(fp, 0L, SEEK_END);
	int sz=ftell(fp);
	fseek(fp,prev,SEEK_SET); //go back to where we were
	return sz;
}

>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
/**
 * order arg:
 * 	- 1: Red
 * 	- 2: Green
 * 	- 3: Blue
 * 	- 4: Alpha
 */
<<<<<<< HEAD
void main(int argc, char *argv[]) {
    // vector to save the order give by the arguments
    char orderArg[5];

    // if the user don't put anyone argument
    if (argc == 1) exit(EXIT_FAILURE);

    // struct that represents the options argument
    static struct option long_options[] = {
            {"Fin"  , required_argument, 0,  'f' },
            {"in"   , required_argument, 0,  'i' },
            {"out"  , required_argument, 0,  'o' },
            {"b"    , required_argument, 0,  'b' },
            {"c"    , required_argument, 0,  'c' },
            {"p"    , required_argument, 0,  'p' },
            {"help" , no_argument,       0,  'h' },
            {0      , 0,  		         0,   0  }
=======
int main(int argc, char *argv[]) {
	if (argc < 2) {
		Log("Insufficient arguments");
		exit(EXIT_FAILURE);
	}
    // vector to save the order give by the arguments
    char orderArg[5];
	int compress = 0;
	char* arg_compress = NULL;
    // struct that represents the options argument
    static struct option long_options[] = {
        {"Fin"  	, required_argument, 0,  'f' },
        {"in"   	, required_argument, 0,  'i' },
        {"out"  	, required_argument, 0,  'o' },
        {"b"    	, required_argument, 0,  'b' },
        {"c"    	, required_argument, 0,  'c' },
        {"p"    	, required_argument, 0,  'p' },
		{"magic"	, required_argument, 0,  'm' },
		{"compress" , no_argument, 0,  'x' },
		{"help" 	, no_argument,       0,  'h' },
        {0      	, 0,  		         0,   0  }
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
    };

    /* getopt_long stores the option index here. */
    int option_index = 0;

<<<<<<< HEAD
    int opt;

    while ((opt = getopt_long_only(argc, argv, "fiobcp:h:",
                                   long_options, &option_index)) != -1) {
        switch (opt) {
            case 'f':
                formatImage = optarg;
                break;
            case 'i':
                pathIn = optarg;
                break;
            case 'o':
                pathOut = optarg;
                break;
            case 'b':
                bitFactor = atoi(optarg);
                break;
            case 'c':
                channels = optarg;
                break;
            case 'p':
                hidePattern = optarg;
                break;
            case 'h':
                puts("HELP -------------");
                puts("-Fin [the flag allows the user to specify the file format for the input image.]");
                puts("     --- Accepted format: PNG, BMP, PPM and PGM");
                puts("-in  [specify the input file to use as image container]");
                puts("     --- This argument is mandatory");
                puts("-out [specify the output file where to store the message - not necessary]");
                puts("     ** in progress **");
                puts("-b   [specify the number of bits to be used when hiding the message]");
                puts("-c   [the channels, as a coma-separated list]");
                puts("     --- The acceptable channel sare Red, Green, Blue, Alpha and Gray.");
                puts("     ** Alpha and Gray: beta version **");
                puts("-p   [specify the pattern to be used to hide the image] - DIRECT/REVEAL");
                puts("     --- Accepted pattern: direct, reverse, external_spiral and internal_spiral");
                puts("     ** in progress **");
                exit(1);
        }
    }

    validPath();
    validBitFactor();
    validChannel();
    validPattern();
    validFormatImage();
    printf("%s - ",pathOut);
=======
	int opt;

	while ((opt = getopt_long_only(argc, argv, "f:i:o:b:c:p:m:x:h",
			    	long_options, &option_index)) != -1) {
	    switch (opt) {
	        case 'f':
		        formatImage = optarg;
				Log(formatImage);
		        break;
	        case 'i':
	        	pathIn = optarg;
				Log(pathIn);
	          	break;
	        case 'o':
	          	pathOut = optarg;
		       	break;
		    case 'b':
	         	bitFactor = atoi(optarg);
				Log(optarg);
	          	break;
	        case 'c':
	         	channels = optarg;
				Log(channels);
	          	break;
	        case 'p':
	         	hidePattern = optarg;
				Log(hidePattern);
	          	break;
			case 'm':
				magic_number = optarg;
				Log(magic_number);
				break;
			case 'x':
				compress = 1;
				arg_compress = optarg;
				LogInt(compress);
				break;
			case 'h':
				puts("HELP -------------");
				puts("-Fin     [the flag allows the user to specify the file format for the input image.]");
				puts("     --- Accepted format: PNG, BMP, PPM and PGM");
				puts("-in      [specify the input file to use as image container]");
				puts("     --- This argument is mandatory");
				puts("-out     [specify the output file where to store the message]");
				puts("     --- If not specified, the tool uses the standard output");
				puts("-b       [specify the number of bits to be used when hiding the message - 1]");
				puts("-c       [the channels, as a coma-separated list] - RED");
				puts("     --- The acceptable channels are Red, Green, Blue, Alpha and Gray.");
				puts("-p       [specify the pattern to be used to hide the image]");
				puts("     --- Accepted pattern: direct, reverse, external_spiral and internal_spiral");
				puts("-magic   [specify the pattern to be used to hide the image]");
				puts("     --- Accepted pattern: direct, reverse, external_spiral and internal_spiral");
				return EXIT_SUCCESS;
	        default:
	            exit(EXIT_FAILURE);
	    }
	}
	imgIn = readImage(pathIn);
	parser(formatImage, pathIn, pathOut, channels, hidePattern, magic_number, bitFactor, imgIn);

	if (!magic_number)
		magic_number = "HELP\0";
	else {
		char substr[3];
		char *ptr_hex = magic_number;
		char magic[strlen(magic_number)];

		for (int i = 0, index = 0; i < strlen(magic_number); i += 2, index++){
			strncpy(substr, ptr_hex, 2);
			int s = strtol(substr, NULL, 16);
			ptr_hex += 2;
			magic[index] = s;
		}
		magic[strlen(magic) - 2] = '\0';
		Log(magic);

		strcpy(magic_number, magic);

		if (strcmp(magic, magic_number) == 0)
			Log("are equals");
	}

	Log(magic_number);

	if (!pathOut)
		pathOut = "resource/output/msg.txt";

>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c

	if ((imgIn->nChannels > 1) && (channels))
		order(channels, orderArg);
	else
		orderArg[0] = '4';

	// run stenography
<<<<<<< HEAD
	steganography(imgIn, bitFactor, orderArg);
}
=======
	stenography(imgIn, pathOut, bitFactor, orderArg, magic_number, hidePattern);

	for (int j = 0; j < argc; ++j) {
		if (strcmp(argv[j], "more") == 0) {
			arg_compress = "more";
		}
	}

	if (compress) {
		if (arg_compress) {
			decompress_more(pathOut);
		} else {
			decompress(pathOut);
		}
	}

	return EXIT_SUCCESS;
}
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
