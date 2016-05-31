cmake_minimum_required (VERSION 3.3)
project (TestPrototype C)
set (CMAKE_C_FLAGS "-std=gnu99 -lm")

find_package (OpenCV REQUIRED)

set (EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
<<<<<<< HEAD
set (CMAKE_C_FLAGS  "-lmagic")
=======
set (CMAKE_C_FLAGS  "-lmagic -w")
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c

link_directories(/usr/local/lib)

include_directories (${OpenCV_INCLUDE_DIRS})

add_executable (
        tests_arguments

        src/minunit_arguments.c
<<<<<<< HEAD
=======
        ../src/util/log.c
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
        ../src/util/checks.c
)
add_executable (
        tests_reveal

        src/minunit_reveal.c
        ../src/util/binary.c
)
add_executable (
<<<<<<< HEAD
        tests_parser

        src/minunit_parser.c
        ../src/util/parser.c
        ../src/util/valitador_argument.c
        ../src/util/checks.c
        ../src/util/Image.c
)
target_link_libraries (
        tests_arguments

        ${OpenCV_LIBS}
        ${Magic_LIBS}
=======
        tests_decompress

        src/minunit_decompress.c
        ../src/decompress/decompress.c
        ../src/util/binary.c
)
add_executable (
        tests_parser

        src/minunit_parser.c
        ../src/util/log.c
        ../src/util/parser.c
        ../src/util/checks.c
        ../src/util/Image.c
)

target_link_libraries (
        tests_arguments
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
)
target_link_libraries (
        tests_reveal

        ${OpenCV_LIBS}
        ${Magic_LIBS}
)
target_link_libraries (
<<<<<<< HEAD
=======
        tests_decompress
)
target_link_libraries (
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
        tests_parser

        ${OpenCV_LIBS}
)