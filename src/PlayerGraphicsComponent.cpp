#include "PlayerGraphicsComponent.hpp"
#include "Util.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

namespace smb
{

PlayerGraphicsComponent::PlayerGraphicsComponent(SDL_Renderer *renderer)
    :  m_renderer{renderer}, 
      m_animator{Animator(m_renderer, "characters.gif", "textCoords.txt")}
{
    m_animator.addAnimation("walk_right", 16, 18);
    m_animator.addAnimation("walk_left", 9, 11);
    m_animator.addAnimation("jump_right", 7, 7);
    m_animator.addAnimation("jump_left", 20, 20);
    m_animator.addAnimation("idle_right", 14, 14);
    m_animator.addAnimation("idle_left", 13, 13);

    m_animator.setAnimation("walk_right");
}

void PlayerGraphicsComponent::render(GameObject &gameObject, SDL_Renderer *)
{
    m_animator.renderAnimation(gameObject.renderBox);
}

Animator &PlayerGraphicsComponent::getAnimator()
{
    return m_animator;
}

} // namespace smb
