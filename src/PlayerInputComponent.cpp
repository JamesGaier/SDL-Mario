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
        gameObject.rect.velocity.x = horizontalSpeed;
    }
    else if (currentKeyStates[SDL_SCANCODE_A])
    {
        gameObject.rect.velocity.x = -horizontalSpeed;
    }
    else
    {
        gameObject.rect.acceleration = Vec2f{0, gameObject.rect.acceleration.y};
        gameObject.rect.velocity = Vec2f{0, gameObject.rect.velocity.y};
    }
}

} // namespace smb