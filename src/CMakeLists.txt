cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)

project(Gomoku)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(PROJECT_SRCS main.cpp ui.cpp)

add_executable(gomoku ${PROJECT_SRCS})

target_link_libraries(gomoku ${SDL2_LIBRARIES})