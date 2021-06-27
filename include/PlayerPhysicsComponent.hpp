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
    ~PlayerPhysicsComponent() = default;

    PlayerPhysicsComponent(std::vector<std::unique_ptr<GameObject>> &world);

    void update(GameObject &gameObject, float dt) override;

  private:
    void AABB(GameObject &gameObject);

    void resolveCollision(GameObject &gameObject, Vec2f &rect);

    bool collision(GameObject &gameObject, Vec2f &ray_dir, const Rect &target, Vec2f contactPoint, Vec2f contactNormal,
                   float &hitNear);

    std::mutex m_updateMutex;
    std::vector<std::unique_ptr<GameObject>> &m_world;
};

} // namespace smb