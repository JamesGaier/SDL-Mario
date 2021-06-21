#pragma once

#include "PhysicsComponent.hpp"
#include "GameObject.hpp"
#include <vector>
#include <memory>
#include <mutex>

namespace smb
{

class PlayerPhysicsComponent : public PhysicsComponent
{
  public:
    ~PlayerPhysicsComponent() = default;
    
    PlayerPhysicsComponent(std::vector<std::unique_ptr<GameObject>> &world);

    void update(GameObject &gameObject, float dt) override;

  private:
    void AABB(GameObject &gameObject);
  
    std::mutex m_updateMutex;
    std::vector<std::unique_ptr<GameObject>> &m_world;
};

} // namespace smb