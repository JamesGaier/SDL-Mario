add_subdirectory(SDL)
add_subdirectory(SDL_image)

add_library(Catch2WithMain 
    STATIC 
    EXCLUDE_FROM_ALL
    catch2/catch_amalgamated.cpp 
)

target_include_directories(Catch2WithMain
    PUBLIC
    catch2
)
