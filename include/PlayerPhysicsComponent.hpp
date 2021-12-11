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

    bool onGround() const;

    void setOnGround(bool onGround);

  private:
    void move(GameObject &go, const float dt);

    GameObject *checkCollision(const GameObject &go);

    std::mutex m_updateMutex;
    World &m_world;
    bool m_onGround{false};
};

} // namespace smb