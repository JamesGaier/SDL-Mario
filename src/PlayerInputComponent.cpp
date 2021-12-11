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
    // currently I am hardcoding in the total number of keys on the keyboard.  I will make my own input class at a later time.
    constexpr auto totalKeys = 104;
    for(size_t i = 0; i < totalKeys; ++i)
    {
        if(keys[i])
        {
            return true;
        }
    }
    return false;
}

void PlayerInputComponent::update(GameObject &gameObject)
{
    const auto *currentKeyStates = SDL_GetKeyboardState(nullptr);
    constexpr auto horizontalSpeed = 300;
    constexpr auto jumpVel = 400;
    constexpr auto jumpAccel = 1000;
    constexpr auto defaultAccel = 800;

    gameObject.accel.y = defaultAccel;
    gameObject.accel = math::Vec2f{0, gameObject.accel.y};
    gameObject.vel = math::Vec2f{0, gameObject.vel.y};

    if (currentKeyStates[SDL_SCANCODE_D])
    {
        gameObject.vel.x = horizontalSpeed;
        m_animator.setAnimation("walk_right");
        m_previousDirection = SDL_SCANCODE_D;
    }

    if (currentKeyStates[SDL_SCANCODE_A])
    {
        gameObject.vel.x = -horizontalSpeed;
        m_animator.setAnimation("walk_left");
        m_previousDirection = SDL_SCANCODE_A;
    }

    if (currentKeyStates[SDL_SCANCODE_X] && m_playerPhysics->onGround())
    {
        gameObject.accel.y = -jumpAccel;
        gameObject.vel.y = -jumpVel;
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
        if(m_previousDirection == SDL_SCANCODE_A)
        {
           m_animator.setAnimation("jump_right"); 
        }
        if(m_previousDirection == SDL_SCANCODE_D)
        {
           m_animator.setAnimation("jump_left"); 
        }
    }
    
    if(!keyPressed(currentKeyStates) && m_playerPhysics->onGround())
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

} // namespace smb
