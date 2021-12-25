cmake_minimum_required(VERSION 3.2)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

project(Mario VERSION 1.0)
include_directories(include)

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)


find_library(SDL2_image NAME SDL2_image)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)


add_custom_target(
    copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
${CMAKE_CURRENT_LIST_DIR}
)
