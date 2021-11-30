#include "PlayerInputComponent.hpp"
#include <chrono>
#include <iostream>

namespace smb
{

void PlayerInputComponent::update(GameObject &gameObject)
{
    const auto *currentKeyStates = SDL_GetKeyboardState(nullptr);
    constexpr auto horizontalSpeed = 300;

    if (currentKeyStates[SDL_SCANCODE_D])
    {
        gameObject.vel.x = horizontalSpeed;
    }
    else if (currentKeyStates[SDL_SCANCODE_A])
    {
        gameObject.vel.x = -horizontalSpeed;
    }
    else if (currentKeyStates[SDL_SCANCODE_X])
    {
    }
    else
    {
        gameObject.accel = Vec2f{0, gameObject.accel.y};
        gameObject.vel = Vec2f{0, gameObject.vel.y};
    }
}

} // namespace smb
