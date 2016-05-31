cmake_minimum_required (VERSION 3.3) #
project (Prototype C)
set (CMAKE_C_FLAGS "-std=gnu99 -lm")

find_package (OpenCV REQUIRED)

<<<<<<< HEAD
set (EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
=======
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
set (CMAKE_C_FLAGS  "-lmagic -w")

link_directories(/usr/local/lib)

include_directories (${OpenCV_INCLUDE_DIRS})

add_executable (
		reveal

		src/main.c
<<<<<<< HEAD

		src/util/checks.c
		src/util/Image.c
		src/util/binary.c

=======
		src/decompress/decompress.c
		src/decompress/decompress_more.c
		src/util/checks.c
		src/util/Image.c
		src/util/binary.c
		src/util/log.c
		src/util/parser.c
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
		src/reveal/reveal.c
		src/reveal/direct/direct_reveal.c
		src/reveal/reverse/reverse_reveal.c
		src/reveal/externalSpiral/externalSpiral_reveal.c
		src/reveal/internalSpiral/internalSpiral_reveal.c
)
target_link_libraries (
	reveal
		
	${OpenCV_LIBS}
	${Magic_LIBS}
)