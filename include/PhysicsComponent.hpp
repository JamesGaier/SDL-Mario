#pragma once
#include "GameObject.hpp"

namespace smb
{

class GameObject;
class PhysicsComponent
{
  public:
    virtual ~PhysicsComponent() = default;
    virtual void update(GameObject &gameObject, float dt) = 0;
};

} // namespace smb