#include "../../includes/validator_argument.h"
#include "../../includes/image.h"

// if we don't have the image format (User), but
// we have the image path, we can check the file signature
// test if the path to input was given and if the path exists
void validPath(char* formatImage, char* pathIn, char* pathOut, IplImage** imgIn) {
    if(!formatImage && (check_imageSignature(pathIn, formatImage) == 0 || check_pathImageIn(pathIn) == 0))
        exit(EXIT_FAILURE);
    else
        *imgIn = readImage(pathIn);

    // test if the path to input was given and if the path exists
    if(pathOut && !check_pathImageOut(pathOut))
        exit(EXIT_FAILURE);
}

// if we have the image format give us by the user
// and the image signature, but they aren't equals
// or don't follow the paterns: error
void validFormatImage(char* formatImage, char* pathIn) {
    if(formatImage && pathIn && (
            (strstr(pathIn, formatImage) == NULL)  ||
            (check_imageSignature(pathIn, formatImage) == 0)  ||
            (check_pathImageIn(pathIn)    == 0)))
        exit(EXIT_FAILURE);
}

// test if the bit factor is valid
void validBitFactor(int bitFactor, IplImage** imgIn) {
    if((*imgIn) && !check_bitFactor(bitFactor, (*imgIn)->depth))
        exit(EXIT_FAILURE);
}

// test if the channels informed by the User are valid
void validChannel(char* pathIn, char* channels, IplImage** imgIn) {
    if(channels && pathIn && !check_channels(channels, (*imgIn)->nChannels, pathIn))
        exit(EXIT_FAILURE);
}

// test if the hide pattern informed is valid
void validPattern(char* hidePattern) {
    if(!check_hidePattern(hidePattern))
        exit(EXIT_FAILURE);
}