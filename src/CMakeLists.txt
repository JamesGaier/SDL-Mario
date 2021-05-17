add_executable(
    Mario 
    main.cpp
    ../include/Window.hpp
)

target_link_libraries(
    Mario
    PRIVATE
    SDL2
)