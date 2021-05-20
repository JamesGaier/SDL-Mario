
add_executable(
    Mario 
    Command.cpp
    Game.cpp
    main.cpp
)

target_compile_options(Mario PRIVATE -Wall -Wextra -Wpedantic -Wnull-dereference)

target_compile_features(Mario PUBLIC cxx_std_17)

target_link_libraries(
    Mario
    PRIVATE
    SDL2
    pthread
)
