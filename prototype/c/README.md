OpenCV
=======

This project was based on the Book **Learning OpenCV 3**:

    Computer Vision in C++ with the OpenCV Library
    Larger Cover
    Learning OpenCV 3
    Computer Vision in C++ with the OpenCV Library
    By Adrian Kaehler, Gary Bradski
    Publisher: O'Reilly Media
    Release Date: September 2015
    Pages: 575
    
There are some data structures importants used by OpenCv API (and basic functions to handle this structures) that require explanations about how its work. This was retired of <a href="http://docs.opencv.org/modules/core/doc/old_basic_structures.html">documentation site</a>  of OpenCV and Illinois [Institute of Technology](http://www.cs.iit.edu/~agam/cs512/lect-notes/opencv-intro/opencv-intro.html#SECTION00053000000000000000)

### What is OpenCv?

OpenCV (Open Source Computer Vision Library) is an open source computer vision and machine learning software library. It contains a large collection of image processing functions. 

The library has more than 2500 optimized algorithms, that can be used to detect and recognize faces, identify objects, classify human actions in videos, track camera movements, track moving objects, extract 3D models of objects, produce 3D point clouds from stereo cameras, follow eye movements, recognize scenery and establish markers to overlay it with augmented reality, etc. 

When executin an OpenCV program, automatically one specify DLL (Dynamic Linked Library) is invokes to detects the processor type and load optimized DLL for this architecture. The OpenCV also works together with the IPL library (Image Processing Library). This library is divided into five functions groups: image processing; structural analysis; motion analysis and object tracking; pattern recognition and camera calibration and 3D reconstruction ([1]).

It has C++, C, Python, Java and MATLAB interfaces and supports Windows, Linux, Android and Mac OS. And the supported image formats are BMP, DIB, JPEG, JPG, JPE, PNG, PBM, PGM, PPM, SR, RAS, TIFF and TIF.

### Some structures and functions OPENCV

#### IplImage
	    - int nSize : sizeof(IplImage)
	    - int nChannels : Number of channels. Most OpenCV functions support 1-4 channels.
	    - int depth : Channel depth in bits + the optional sign bit (IPL_DEPTH_8U, IPL_DEPTH_8S, IPL_DEPTH_16U,  IPL_DEPTH_16S, IPL_DEPTH_32S, IPL_DEPTH_32F, IPL_DEPTH_64F)
	    - int width: Image width in pixels
	    - int height: Image height in pixels
	    - IplROI* roi: Region Of Interest (ROI). If not NULL, only this image region will be processed
	    - int imageSize/ Image data size in bytes. For interleaved data, this equals `image->height` and `image->widthStep`
	    - char* imageData: A pointer to the aligned image data. Do not assign imageData directly. Use SetData()
	    - int widthStep: The size of an aligned image row, in bytes.


#### CvMat 
	- int   type : elements type (uchar, short, int, float, double) and flags
	- int   step : full row length in bytes
	- int   rows, cols : dimensions
	- int   height, width : alternative dimensions reference union data
	- uchar*  ptr : data pointer for an unsigned char matrix
	- short*  s : data pointer for a short matrix
	- int*  i : data pointer for an integer matrix
	- float*  fl : data pointer for a float matrix
	- double* db : data pointer for a double matrix

cvMat (or Mat in C++) is basically a class with two data parts: the matrix header (containing information such as the size of the matrix, the method used for storing, at which address is the matrix stored, and so on) and a pointer to the matrix containing the pixel values (taking any dimensionality depending on the method chosen for storing). The matrix header size is constant, however the size of the matrix itself may vary from image to image and usually is larger by orders of magnitude.

#### Points:

	-	2D point with integer coordinates (usually zero-based).


```C
CvPoint      p = cvPoint(int x, int y);
CvPoint2D32f p = cvPoint2D32f(float x, float y);
CvPoint3D32f p = cvPoint3D32f(float x, float y, float z);
```


**param x**:	x-coordinate of the point.
**param y**:	y-coordinate of the point.
**param point**:	the point to convert.


#### CvSize

	-	Size of a rectangle or an image.
```C
CvSize       r = cvSize(int width, int height);
CvSize2D32f  r = cvSize2D32f(float width, float height);
Rectangular dimensions with offset:
CvRect       r = cvRect(int x, int y, int width, int height);
```

**width** : width of the rectangle.
**height** : height of the rectangle.

#### CvRect 
	-	Stores coordinates of a rectangle.

```C 
CvRect cvRect(int x, int y, int width, int height)
``` 

**x** : x-coordinate of the top-left corner.
**y** : y-coordinate of the top-left corner (sometimes bottom-left corner).
**width** : width of the rectangle.
**height** : height of the rectangle.


> **Note:** You can find more information about **OpenCv Structures** [here][1].

----------


Before starting
-------------

#### <i class="icon-file"></i> Create a image

``` C
IplImage* cvCreateImage(CvSize size, int depth, int channels);
```
We can use this code to create an image header and allocates the image data.

**size**:  Image width and height, cvSize(width, height);

 **depth**: pixel depth in bits: IPL_DEPTH_8U, IPL_DEPTH_8S, IPL_DEPTH_16U, IPL_DEPTH_16S, IPL_DEPTH_32S, IPL_DEPTH_32F, IPL_DEPTH_64F

**channels**: Number of channels per pixel. Can be 1, 2, 3 or 4. The usual data layout of a color image is b0 g0 r0 b1 g1 r1 ...

#### <i class="icon-plus"></i> Clone

Makes a full copy of an image, including the header, data, and ROI.

``` C
IplImage* img1 = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1); 
IplImage* img2;
img2=cvCloneImage(img1);
```

**image**: The original image

#### <i class="icon-picture"></i> Reading and writing images

##### Reading an image from a file:

```C
IplImage* img=0; 
  img=cvLoadImage(fileName);
  if(!img) printf("Could not load image file: %s\n",fileName);
```
The OpenCV supported image formats: BMP, DIB, JPEG, JPG, JPE, PNG, PBM, PGM, PPM, SR, RAS, TIFF, TIF.

##### Writing an image from a file:

```
if(!cvSaveImage("image.jpg", &point_from_image)) 
	printf("Could not save: %s\n", outFileName);
```
The output file format is determined based on the file name extension.

#### <i class="icon-pencil"></i> Accessing image elements

For multichannel images the columns contain as many sub columns as the number of channels. [For example](http://docs.opencv.org/doc/tutorials/core/how_to_scan_images/how_to_scan_images.html) in case of an RGB color system:

![alt tag](http://docs.opencv.org/_images/math/b6df115410caafea291ceb011f19cc4a19ae6c2c.png)

Assume that you need to access the *k*-th channel of the pixel at the *i*-row and *j*-th column. The row index *i* is in the range  *[0, height - 1]*. The column index *j* is in the range *[0, width - 1]*. The channel index *k* is in the range  *[0, nchannels - 1]*. 
We can access the pixels with three ways [2]:

##### Indirect access: 

The more popular way is using supplied accessor functions. For example, to obtain the size of a matrix, you can get the information you want either by calling cvGetSize(CvMat*), which returns a CvSize structure. In this case, you can use the CvGet2D(*IplImage, row, column) to obtain the (row,column) pixel value.

```
IplImage* img=cvCreateImage(cvSize(640, 480), IPL_DEPTH_32F, 3);

CvScalar s;
s = cvGet2D(img,i,j);

printf("B = %f, G = %f, R = %f\n", s.val[0], s.val[1], s.val[2]);

s.val[0]=111;
s.val[1]=111;
s.val[2]=111;

cvSet2D(img,i,j,s); // set the (i,j) pixel value
```

##### Direct access with pointer: 

```C
int height     = image->height;
int width      = image->width;
int step       = image->widthStep/sizeof(uchar);
int channels   = image->nChannels;
uchar* data    = (uchar *)image->imageData;
		
unsigned char r = data[i * step + j * channels + 2];
unsigned char g = data[i * step + j * channels + 1];
unsigned char b = data[i * step + j * channels + 0]; 
		 
printf("Current Position: x= %d y= %d B= %d G= %d R= %d\n", i , j , b , g , r);
```
Ok. It's very confusing. First, when we use ```widthStep```, we access the length of a row in bytes (not ints or floats!!!) and ```imageData``` we take a pointer to a data array (and some more stuff).

If this is complicate for you, it's good see the next example gived in a [forum](http://stackoverflow.com/questions/13554244/how-to-use-pointer-expressions-to-access-elements-of-a-two-dimensional-array-in):
	
    The **arra** is a pointer to first sub array,
    arr:
        will be pointer to first sub array, not the first element of first sub 
        array, according to relationship of array & pointer, it also represent 
        the array itself,

    arr+1:
        will be pointer to second sub array, not the second element of first sub 
        array,

    *(arr+1):
        will be pointer to first element of second sub array,
        according to relationship of array & pointer, it also represent second
        sub array, same as arr[1],

    *(arr+1)+2:
        will be pointer to third element of second sub array,

    *(*(arr+1)+2):
        will get value of third element of second sub array,
        same as arr[1][2],

----------

  [1]: http://seer.ufrgs.br/rita/article/viewFile/rita_v16_n1_p125/7289
  [3]: http://docs.opencv.org/modules/core/doc/old_basic_structures.html
  [2]: http://www.cs.iit.edu/~agam/cs512/lect-notes/opencv-intro/opencv-intro.html#SECTION00053000000000000000
 




