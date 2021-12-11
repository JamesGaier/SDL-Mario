#pragma once
#include "InputComponent.hpp"
#include "PlayerGraphicsComponent.hpp"
#include "PlayerPhysicsComponent.hpp"
#include "Animator.hpp"
#include <SDL.h>
#include <memory>

namespace smb
{

class PlayerInputComponent : public InputComponent
{
  public:
    ~PlayerInputComponent() = default;
    PlayerInputComponent(PlayerPhysicsComponent *playerPhysics, PlayerGraphicsComponent *graphicsComponent, SDL_Renderer *renderer);
    void update(GameObject &gameObject);
    bool keyPressed(const unsigned char *keys);

  public:
    PlayerPhysicsComponent *m_playerPhysics;
    PlayerGraphicsComponent *m_playerGraphics;
    SDL_Renderer *m_renderer;
    Animator &m_animator;
    bool m_jumping;
    int m_previousDirection{SDL_SCANCODE_A};
};

} // namespace smb
