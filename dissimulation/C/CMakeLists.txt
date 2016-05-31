cmake_minimum_required (VERSION 3.3)
project (Prototype C)
set (CMAKE_C_FLAGS "-std=gnu99 -lm")

find_package (OpenCV REQUIRED)

set (EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

include_directories (${OpenCV_INCLUDE_DIRS})

add_executable (
	dissimulation
	
	main.c
)
target_link_libraries (
	dissimulation
		
	${OpenCV_LIBS}
)