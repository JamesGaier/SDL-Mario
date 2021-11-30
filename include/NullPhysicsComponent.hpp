#pragma once

#include "PhysicsComponent.hpp"

namespace smb
{

class NullPhysicsComponent final : public PhysicsComponent
{
  public:
    ~NullPhysicsComponent() override = default;
    void update(GameObject &, float) override
    {
    }
};

} // namespace smb