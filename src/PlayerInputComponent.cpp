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
        gameObject.velocity.x = horizontalSpeed;
    }
    else if (currentKeyStates[SDL_SCANCODE_A])
    {
        gameObject.velocity.x = -horizontalSpeed;
    }
    else
    {
        gameObject.acceleration = Vec2f{0, gameObject.acceleration.y};
        gameObject.velocity = Vec2f{0, gameObject.velocity.y};
    }
}

} // namespace smb