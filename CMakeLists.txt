project(FalconEngine)
cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/jsoncpp)

# doxygen staff
configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
include(FindDoxygen)
if(DOXYGEN_FOUND)
	# для ручного запуска, CI делает через плагин
	add_custom_target(
		doc
		COMMENT "Doxygen documentation" DEPENDS
		${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-Wall) 
add_definitions(-D_REENTRANT)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/firefly)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/game)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/firefly)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/game)

add_subdirectory(src)
