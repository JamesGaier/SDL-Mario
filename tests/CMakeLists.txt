set(
    MARIO_TESTS
    ${CMAKE_CURRENT_LIST_DIR}/MathTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MainTests.cpp
)

add_executable(
    MarioTest
    ${MARIO_TESTS}
)

target_compile_options(MarioTest PRIVATE -Wall -Wextra -Wpedantic -Wnull-dereference -fsanitize=address,undefined -g)

target_compile_features(MarioTest PUBLIC cxx_std_17)


target_link_libraries(
    MarioTest
    PRIVATE
    -fsanitize=address,undefined
    SDL2
    Catch2WithMain
    SDL2_image
    pthread
)

