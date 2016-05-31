## Revelation

#### Base
- **Fin**: *the flag allows the user to specify the file format for the input image.*
	- Accepted format: PNG, BMP, PPM and PGM
	- If not specified, the tool detects the format automatically.
- **in** : *specify the input file to use as image container*
	- This argument is mandatory
- **out**: *specify the output file where to store the message*
	- If not specified, the tool uses the standard out put
- **b** : *specify the number of bits to be used when hiding the message*
	- If not specified, the default value is 1 
- **c** : *the channels, as a coma-separated list*
    - The acceptable channel sare Red, Green, Blue, Alpha and Gray.
	- Default values are Red, Green, Blue for colored image and Gray for gray based ones
	- The tool will reject a channel that does not exist in the image container.
- **p** : *specify the pattern to be used to hide the image*
	- "direct" stores the message line by line, starting by the first line
	- "reverse" stores the message line by line, starting by the last one 
	- "external_spiral" stores the message using a clockwise spiral pattern, 
		starting in the top-left corner and following the external border of the image
	- "internal_spiral" stores the message using a clockwise spiral pattern starting at the middle of the picture, and then going top, then right, ... 
	- The default valueis "direct"


#### high-level project directories

<!-- language:console -->
    revelation/
        include/
        lib/
        resource/
        src/
            reveal/
                direct/
                reverse/
                reveal.c
            util/
            main.c
        tests/
        bash.sh
        CMakeLists.txt
        Readme.md

   - **bin**: Compiled exe
   - **includes**: Headers
   - **lib**: third-party lib files (dependencies)
   - **resource**: image data base
   - **src**: source files 
   - **tests**: tests files

#### features

- Command Line Interface
- Validating arguments
- Tests (minunit)
- Recovery message
- Script test (calculate of the execution time and compare with the original file)

#### dependencies
  * [libmagic](http://vivithemage.co.uk/blog/?p=105) 
        - Libmagic is generally used to determine a file type, for example if it’s a jpg, avi, or whatever, you can point it to a file and it will determine what sort of file it is using magic numbers.

  * [OPENCV](http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html) 
        - OpenCV (Open Source Computer Vision Library: http://opencv.org) is an open-source BSD-licensed library that includes several hundreds of computer vision algorithms. The document describes the so-called OpenCV 2.x API, which is essentially a C++ API, as opposite to the C-based OpenCV 1.x API. The latter is described in opencv1x.pdf.
   
  * [CMake VERSION 3.3](https://cmake.org/install/) 
          - CMake is used to control the software compilation process using simple platform and compiler independent configuration files.

How we used this lib:
    
    #include <magic.h>
    (...)
    int check_imageSignature(char* filename) {
        magic_t handle = magic_open(MAGIC_NONE|MAGIC_COMPRESS);
        magic_load(handle, NULL);

        const char * type = magic_file(handle, filename);

        if (type) {
            if(strstr(type, "PNG") != NULL)
                return 1;
            else if(strstr(type, "bitmap") != NULL)
                return 1;
            else if(strstr(type, "pixmap") != NULL)
                return 1;
            else if(strstr(type, "greymap") != NULL)
                return 1;
            else
                return 0;
        }

        magic_close(handle);
        return 0;
    }
    

#### functions

* [getopt_long_only()](http://linux.die.net/man/3/getopt_long_only)

```
int getopt_long_only (int argc, char *const *argv, const char *shortopts, const struct option *longopts, int indexptr);
```

The getopt_long_only() function parses the command-line arguments. If getopt_long_only() is called repeatedly, it returns successively each of the option characters from each of the option elements. If there are no more option characters, getopt_long_only() returns -1. getopt_long_only() is like getopt_long(), but '-' as well as "--" can indicate a long option. 

* [strcasecmp()](https://en.wikibooks.org/wiki/C_Programming/C_Reference/nonstandard/strcasecmp)

```
int strcasecmp(const char *f1, const char *f2);
```

In programming language C, strcasecmp is a function declared in the strings.h header file (or sometimes in string.h) that compares two strings irrespective of the case of characters.

This function returns an integer i :
	- i > 0, if lowercase(f1) is greater than lowercase(f2)
	- i < 0, if lowercase(f1) is found less than string lowercase(f2) and
	- i = 0, if lowercase(f1) is equal to lowercase(f2).

* [stat()](http://codewiki.wikidot.com/c:system-calls:stat)

```
int stat(const char *path, struct stat *buf);
```

**stat** is a system call that is used to determine information about a file based on its file path.
We used this function to check if the file path exists.

```
int check_pathImageOut(const char* filename) {
    struct stat buf;
    malloc(sizeof(struct stat));
    return (stat(filename, &buf) == 0);
}
```

#### tests

* [minunit](https://github.com/siu/minunit)

[source explanation](https://github.com/siu/minunit)

Minunit is a minimal unit testing framework for C/C++ self-contained in a
single header file.

It provides a way to define and configure test suites and a few handy assertion
types.  It reports the summary of the number of tests run, number of assertions
and time elapsed.

##### How to use it

This is a minimal test suite written with minunit:

	#include "minunit.h"

	MU_TEST(test_check) {
		mu_check(5 == 7);
	}
	MU_TEST_SUITE(test_suite) {
		MU_RUN_TEST(test_check);
	}

	int main(int argc, char *argv[]) {
		MU_RUN_SUITE(test_suite);
		MU_REPORT();
		return 0;
	}

Which will produce the following output:

	F
	test_check failed:
		readme_sample.c:4: 5 == 7


	1 tests, 1 assertions, 1 failures

	Finished in 0.00032524 seconds (real) 0.00017998 seconds (proc)

Check out minunit_example.c to see a complete example. Compile with something
like:

	gcc minunit_example.c -lrt -lm -o minunit_example

Don't forget to add -lrt for the timer and -lm for linking the function fabs
used in mu_assert_double_eq.
