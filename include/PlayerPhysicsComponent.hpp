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
    void move(GameObject &go, const unsigned long ID, const float dt);

    std::mutex m_updateMutex;
    World &m_world;
    bool m_onGround{false};
    bool m_jumping{false};
};

} // namespace smb