#pragma once

#include "PhysicsComponent.hpp"

namespace smb
{

class NullPhysicsComponent final : public PhysicsComponent
{
  public:
    ~NullPhysicsComponent() override = default;
    void update(GameObject &gameObject, float dt) override
    {
    }
};

} // namespace smb