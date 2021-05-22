
set(
    MARIO_SRCS 
    ${CMAKE_SOURCE_DIR}/src/Command.cpp
    ${CMAKE_SOURCE_DIR}/src/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

add_executable(
    Mario 
    ${MARIO_SRCS}
)

add_custom_target(fmt COMMAND clang-format -i -style=file ${MARIO_SRCS} ${CMAKE_SOURCE_DIR}/include/*.hpp USES_TERMINAL)

target_compile_options(Mario PRIVATE -Wall -Wextra -Wpedantic -Wnull-dereference -fsanitize=address -g)

target_compile_features(Mario PUBLIC cxx_std_17)

target_link_libraries(
    Mario
    PRIVATE
    -fsanitize=address
    SDL2
    SDL2_image
    pthread
)
