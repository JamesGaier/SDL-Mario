#pragma once

#include "PhysicsComponent.hpp"

namespace smb
{
    
class PlayerPhysicsComponent : public PhysicsComponent    
{
public:
    ~PlayerPhysicsComponent() = default;
    
    void update(GameObject &gameObject, float dt) override;
};
    
    
}