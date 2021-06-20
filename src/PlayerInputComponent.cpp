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
        gameObject.m_velocity.x = horizontalSpeed;
    }
    else if (currentKeyStates[SDL_SCANCODE_A])
    {
        gameObject.m_velocity.x = -horizontalSpeed;
    }
    else
    {
        gameObject.m_acceleration = Vec2<float>{0, gameObject.m_acceleration.y};
        gameObject.m_velocity = Vec2<float>{0, gameObject.m_velocity.y};
    }
}

} // namespace smb