#pragma once

#include "GameObject.hpp"
#include "PhysicsComponent.hpp"
#include <memory>
#include <mutex>
#include <vector>

namespace smb
{

class PlayerPhysicsComponent : public PhysicsComponent
{
  public:
  using World = std::vector<std::unique_ptr<GameObject>>; 
    ~PlayerPhysicsComponent() = default;

    PlayerPhysicsComponent(World &world);

    void update(GameObject &gameObject, float dt) override;

  private:
    void AABB(GameObject &gameObject, const float dt);

    std::mutex m_updateMutex;
    World &m_world;
};

} // namespace smb