#include "../../includes/parser.h"
<<<<<<< HEAD
#include "../../includes/validator_argument.h"
#include <getopt.h>
#include <stdio.h>

/**
 * Method parser responsible to read the arguments.
 */
int parser(int argc, char *argv[], char** formatImage, char** pathIn, char** pathOut,
           char** hidePattern, char** channels, int* bitFactor, IplImage** imgIn) {

    // if the user don't put anyone argument
    if (argc == 1) return (EXIT_FAILURE);

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
    };

    /* getopt_long stores the option index here. */
    int option_index = 0;

    int opt;

    while ((opt = getopt_long_only(argc, argv, "fiobcp:h:",
                                   long_options, &option_index)) != -1) {
        switch (opt) {
            case 'f':
                *formatImage = optarg;
                break;
            case 'i':
                *pathIn = optarg;
                break;
            case 'o':
                *pathOut = optarg;
                break;
            case 'b':
                *bitFactor = atoi(optarg);
                break;
            case 'c':
                *channels = optarg;
                break;
            case 'p':
                *hidePattern = optarg;
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

    validPath(*formatImage, *pathIn, *pathOut, imgIn);
    validBitFactor(*bitFactor, imgIn);
    validChannel(*pathIn, *channels, imgIn);
    validPattern(*hidePattern);
    validFormatImage(*formatImage, *pathIn);

    return 1;
}
=======
#include "../../includes/log.h"
#include "../../includes/arguments.h"

int parser(char* formatImage, char* pathIn, char* pathOut, char* channels, char* hidePattern, char* magic, int bitFactor, IplImage* imgIn) {
    // if we have the image format give us by the user and the image signature, but they aren't equals
    // or don't follow the patterns: error
    if(formatImage && pathIn &&
       (strstr(pathIn, formatImage) == NULL)) {
        Log("error with the format image and the argument Fin");
        if ((check_imageSignature(pathIn, &formatImage) == EXIT_FAILURE  ||
             check_pathImageIn(pathIn) == EXIT_FAILURE))
            exit(EXIT_FAILURE);
        exit(EXIT_FAILURE);
    }

    // if we don't have the image format (User), but we have the image path, we can check the file signature
    // test if the path to input was given and if the path exists
    if(!formatImage && (check_pathImageIn(pathIn) == EXIT_FAILURE))
        exit(EXIT_FAILURE);

    // test if the path to input was given and if the path exists
    if(pathOut && check_pathImageOut(pathOut) == EXIT_FAILURE)
        exit(EXIT_FAILURE);

    // test if the bit factor is valid
    if(imgIn && check_bitFactor(bitFactor, imgIn->depth) == EXIT_FAILURE)
        exit(EXIT_FAILURE);

    // test if the channels informed by the User are valid
    if(channels && pathIn && check_channels(channels, imgIn->nChannels, pathIn) == EXIT_FAILURE)
        exit(EXIT_FAILURE);

    // test if the hide pattern informed is valid
    if(check_hidePattern(hidePattern) == EXIT_FAILURE)
        exit(EXIT_FAILURE);

    Log("-- arguments passed --");

    return EXIT_SUCCESS;
}
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
