#pragma once
#include "InputComponent.hpp"
#include "PlayerPhysicsComponent.hpp"
#include <SDL.h>
#include <memory>

namespace smb
{

class PlayerInputComponent : public InputComponent
{
  public:
    ~PlayerInputComponent() = default;
    PlayerInputComponent(PlayerPhysicsComponent *playerPhysics);
    void update(GameObject &gameObject);
  public:
    PlayerPhysicsComponent *m_playerPhysics;
};

} // namespace smb