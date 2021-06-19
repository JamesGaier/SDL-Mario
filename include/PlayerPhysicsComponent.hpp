#pragma once

#include "PhysicsComponent.hpp"
#include <mutex>

namespace smb
{

class PlayerPhysicsComponent : public PhysicsComponent
{
  public:
    ~PlayerPhysicsComponent() = default;
    
    void update(GameObject &gameObject, float dt) override;

  private:
    std::mutex m_updateMutex;
};

} // namespace smb