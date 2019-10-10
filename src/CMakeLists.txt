cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)

project(gomoku)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED >=2.0.0)

set(PROJECT_SRCS
	main.cpp
	Menu.cpp
	Parameters.cpp
	ui.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SRCS})

target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image)