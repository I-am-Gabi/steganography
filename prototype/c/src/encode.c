//Mathieu Mérino
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

enum COLOR {
    BLUE =  0,
    GREEN = 1,
    RED =   2
};

struct pixel{
    unsigned char val[3];
};
struct pixel getPixel(int i, int j, IplImage* img){
    struct pixel p;
    p.val[BLUE]     = (img->imageData + i*img->widthStep)[j*img->nChannels + BLUE]; //Blue
    p.val[GREEN]    = (img->imageData + i*img->widthStep)[j*img->nChannels + GREEN]; //Green
    p.val[RED]      = (img->imageData + i*img->widthStep)[j*img->nChannels + RED]; //Red
    return p;
}
void setPixel(int i, int j, IplImage* img, struct pixel p){
    (img->imageData + i*img->widthStep)[j*img->nChannels + BLUE]    = p.val[BLUE];
    (img->imageData + i*img->widthStep)[j*img->nChannels + GREEN]   = p.val[GREEN];
    (img->imageData + i*img->widthStep)[j*img->nChannels + RED]     = p.val[RED];
}
void saveImage(IplImage* img, char* file){
    cvSaveImage(file, img, 0);
}
void encodeText(IplImage* img, char* text){

}
void test1(){
    char * filePath = "../resources/rgb.png";
    IplImage* img = cvLoadImage(filePath, 1);
    struct pixel p = getPixel(0, 0, img);
    printf("%d %d %d\n", p.val[0], p.val[1], p.val[2]);
    p.val[0] = 255;
    setPixel(0, 0, img, p);
    printf("%d %d %d\n", p.val[0], p.val[1], p.val[2]);
    saveImage(img, "encode_result.png");
    int a;
    scanf("%d", &a);
}
int main (){
    test1();
}