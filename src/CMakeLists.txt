
set(
    MARIO_SRCS 
    ${CMAKE_SOURCE_DIR}/src/Animator.cpp
    ${CMAKE_SOURCE_DIR}/src/Camera.cpp
    ${CMAKE_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/GameObject.cpp
    ${CMAKE_SOURCE_DIR}/src/Level.cpp
    ${CMAKE_SOURCE_DIR}/src/PlayerGraphicsComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/PlayerInputComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/PlayerPhysicsComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/ResourceFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/StaticTileGraphicsComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/File.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

add_executable(
    Mario 
    ${MARIO_SRCS}
)

add_custom_target(fmt COMMAND clang-format -i -style=file ${MARIO_SRCS} ${CMAKE_SOURCE_DIR}/include/*.hpp USES_TERMINAL)

target_compile_options(Mario PRIVATE -Wall -Wextra -Wpedantic -Wnull-dereference -fsanitize=address,undefined -g)

target_compile_features(Mario PUBLIC cxx_std_17)

target_link_libraries(
    Mario
    PRIVATE
    -fsanitize=address,undefined
    SDL2
    SDL2_image
    pthread
)

