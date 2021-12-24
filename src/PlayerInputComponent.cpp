#include "PlayerInputComponent.hpp"
#include "PlayerGraphicsComponent.hpp"
#include <chrono>
#include <iostream>

namespace smb
{

PlayerInputComponent::PlayerInputComponent(PlayerPhysicsComponent *physicsComponent,
                                           PlayerGraphicsComponent *graphicsComponent, SDL_Renderer *renderer)
    : m_playerPhysics{physicsComponent}, m_playerGraphics{graphicsComponent}, m_renderer{renderer},
      m_animator{m_playerGraphics->getAnimator()}
{
}

bool PlayerInputComponent::keyPressed(const unsigned char *keys)
{
    // currently I am hardcoding in the total number of keys on the keyboard.  I will make my own input class at a later
    // time.
    constexpr auto totalKeys = 104;
    for (size_t i = 0; i < totalKeys; ++i)
    {
        if (keys[i])
        {
            return true;
        }
    }
    return false;
}

void PlayerInputComponent::walk(const unsigned char *keys, GameObject &gameObject)
{
    constexpr auto horizontalSpeed = 300;
    if (keys[SDL_SCANCODE_D])
    {
        gameObject.setVelocityX(horizontalSpeed);
        m_animator.setAnimation("walk_right");
        m_previousDirection = SDL_SCANCODE_D;
    }

    if (keys[SDL_SCANCODE_A])
    {
        gameObject.setVelocityX(-horizontalSpeed);
        m_animator.setAnimation("walk_left");
        m_previousDirection = SDL_SCANCODE_A;
    }
}

void PlayerInputComponent::jump(const unsigned char *keys, GameObject &gameObject)
{
    constexpr auto jumpVel = 400;
    constexpr auto jumpAccel = 1000;
    if (keys[SDL_SCANCODE_X] && m_playerPhysics->onGround())
    {
        gameObject.setAccelerationY(-jumpAccel);
        gameObject.setVelocityY(-jumpVel);
        m_playerPhysics->setOnGround(false);
        if (m_previousDirection == SDL_SCANCODE_A)
        {
            m_animator.setAnimation("jump_right");
        }
        else if (m_previousDirection == SDL_SCANCODE_D)
        {
            m_animator.setAnimation("jump_left");
        }
    }

    if (!m_playerPhysics->onGround())
    {
        if (m_previousDirection == SDL_SCANCODE_A)
        {
            m_animator.setAnimation("jump_right");
        }
        if (m_previousDirection == SDL_SCANCODE_D)
        {
            m_animator.setAnimation("jump_left");
        }
    }
}

void PlayerInputComponent::idle(const unsigned char *keys)
{
    if (!keyPressed(keys) && m_playerPhysics->onGround())
    {
        if (m_previousDirection == SDL_SCANCODE_A)
        {
            m_animator.setAnimation("idle_left");
        }
        else if (m_previousDirection == SDL_SCANCODE_D)
        {
            m_animator.setAnimation("idle_right");
        }
    }
}

void PlayerInputComponent::update(GameObject &gameObject)
{
    const auto *currentKeyStates = SDL_GetKeyboardState(nullptr);
    constexpr auto defaultAccel = 800;

    gameObject.setAccelerationY(defaultAccel);
    gameObject.setVelocityX(0);

    walk(currentKeyStates, gameObject);
    jump(currentKeyStates, gameObject);
    idle(currentKeyStates);
}

} // namespace smb
