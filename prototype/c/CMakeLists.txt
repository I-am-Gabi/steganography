cmake_minimum_required (VERSION 3.3)
project (Prototype C)
set (CMAKE_C_FLAGS "-std=gnu99 -lm")
#set (OpenCV_STATIC OFF)
find_package (OpenCV REQUIRED)

set (EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")
include_directories (${OpenCV_INCLUDE_DIRS})

add_executable (
	nb
	
	src/nb.c
)
add_executable (
	cvPyrDown
	
	src/cvPyrDown.c
)
add_executable (
	filterC
	
	src/filterC.c
)
add_executable (
	infoImage
	
	src/infoImage.c
)
add_executable (
	main
	
	src/main.c
)
add_executable (
	negative
	
	src/negative.c
)
add_executable (
	rgb
	
	src/rgb.c
)
add_executable (
	rotating
	
	src/rotating.c
)
add_executable (
	smoothing
	
	src/smoothing.c
)
add_executable (
	ycrcb
	
	src/ycrcb.c
)
add_executable (
	resize
	
	src/resize.c
)
add_executable(
	encode
	
	src/encode.c
)
add_executable(
	byte
	
	src/byte.c
)
add_executable(
	cut
	
	src/cut.c
)

target_link_libraries(
	nb
	
	${OpenCV_LIBS}
)
target_link_libraries (
	cvPyrDown
		
	${OpenCV_LIBS}
)
target_link_libraries (
	filterC
		
	${OpenCV_LIBS}
)
target_link_libraries (
	infoImage
		
	${OpenCV_LIBS}
)
target_link_libraries (
	main
		
	${OpenCV_LIBS}
)
target_link_libraries (
	negative
		
	${OpenCV_LIBS}
)
target_link_libraries (
	rgb
		
	${OpenCV_LIBS}
)
target_link_libraries (
	rotating
		
	${OpenCV_LIBS}
)
target_link_libraries (
	smoothing
		
	${OpenCV_LIBS}
)
target_link_libraries (
	ycrcb
		
	${OpenCV_LIBS}
)
target_link_libraries (
	resize
		
	${OpenCV_LIBS}
)
target_link_libraries (
	encode
		
	${OpenCV_LIBS}
)
target_link_libraries (
	byte
		
	${OpenCV_LIBS}
)
target_link_libraries (
	cut
		
	${OpenCV_LIBS}
)