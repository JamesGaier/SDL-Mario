
add_executable(
    Mario 
    Command.cpp
    Game.cpp
    main.cpp
    ../include/Command.hpp
    ../include/Game.hpp
    ../include/Util.hpp
)

target_compile_features(Mario PUBLIC cxx_std_17)

target_link_libraries(
    Mario
    PRIVATE
    SDL2
    pthread
)
