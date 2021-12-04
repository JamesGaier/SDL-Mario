#include "PlayerInputComponent.hpp"
#include <chrono>
#include <iostream>

namespace smb
{

PlayerInputComponent::PlayerInputComponent(PlayerPhysicsComponent *physicsComponent)
: m_playerPhysics{physicsComponent}
{
}

void PlayerInputComponent::update(GameObject &gameObject)
{
    const auto *currentKeyStates = SDL_GetKeyboardState(nullptr);
    constexpr auto horizontalSpeed = 300;
    constexpr auto jumpHeight = 500;
    constexpr auto defaultAccel = 800;

    gameObject.accel.y = defaultAccel;
    gameObject.accel = math::Vec2f{0, gameObject.accel.y};
    gameObject.vel = math::Vec2f{0, gameObject.vel.y};

    if (currentKeyStates[SDL_SCANCODE_D])
    {
        gameObject.vel.x = horizontalSpeed;
    }
    if (currentKeyStates[SDL_SCANCODE_A])
    {
        gameObject.vel.x = -horizontalSpeed;
    }
    if (currentKeyStates[SDL_SCANCODE_X])
    {
        if(m_playerPhysics->onGround())
        {
            gameObject.accel.y = -1000;
            gameObject.vel.y = -400;
            m_playerPhysics->setOnGround(false);
        }
    }
}

} // namespace smb
