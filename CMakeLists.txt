cmake_minimum_required(VERSION 3.2)
project(Mario VERSION 1.0)
include_directories(include)

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)

add_subdirectory(external)
add_subdirectory(src)