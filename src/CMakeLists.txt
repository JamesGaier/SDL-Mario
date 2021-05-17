add_executable(
    Mario 
    main.cpp
    Window.cpp
    ../include/Window.hpp
    ../include/Util.hpp
)

target_link_libraries(
    Mario
    PRIVATE
    SDL2
)