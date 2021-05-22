# build SDL
git clone https://github.com/libsdl-org/SDL
mkdir SDL_build && cd SDL_build
cmake ../SDL -DCMAKE_INSTALL_PREFIX=install
cmake --build . --target install

# build SDL_image
cd .. # return from SDL_build directory
git clone https://github.com/libsdl-org/SDL_image
mkdir SDL_image_build && cd SDL_image_build
cmake ../SDL_image -DSDL2_DIR=../SDL_build/install/lib/cmake/SDL2
cmake --build .
