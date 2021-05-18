

add_executable(
    Mario 
    main.cpp
    Game.cpp
    ../include/Game.hpp
    ../include/Util.hpp
)

add_compile_options(-std=c++17) 

target_link_libraries(
    Mario
    PRIVATE
    SDL2
    pthread
)
