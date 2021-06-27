#include "PlayerPhysicsComponent.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace smb
{

PlayerPhysicsComponent::PlayerPhysicsComponent(std::vector<std::unique_ptr<GameObject>> &world) : m_world{world}
{
}

void PlayerPhysicsComponent::update(GameObject &gameObject, float dt)
{
    std::lock_guard<std::mutex> lg{m_updateMutex};
    gameObject.velocity += gameObject.acceleration * dt;
    gameObject.rect.pos += gameObject.velocity * dt;
    AABB(gameObject);
}

bool PlayerPhysicsComponent::collision(GameObject &gameObject, Vec2f &rayDir, const Rect &target, Vec2f contactPoint,
                                       Vec2f contactNormal, float &hitNear)
{
    contactNormal = {0, 0};
    contactPoint = {0, 0};

    // cache division
    Vec2f invDir = 1.0f / rayDir;

    Vec2f tNear = (target.pos - gameObject.rect.pos);
    Vec2f tFar = (target.pos + target.size - gameObject.rect.pos) * invDir;

    // accounts for divide by zero errors
    if (std::isnan(tFar.y) || std::isnan(tFar.x))
        return false;
    if (std::isnan(tNear.y) || std::isnan(tNear.x))
        return false;

    // Sort distance
    if (tNear.x > tFar.x)
        std::swap(tNear.x, tFar.x);
    if (tNear.y > tFar.y)
        std::swap(tNear.y, tFar.y);

    // Early rejection
    if (tNear.x > tFar.y || tNear.y > tFar.x)
        return false;

    hitNear = std::max(tNear.x, tNear.y);

    float hitFar = std::min(tFar.x, tFar.y);

    // Reject if ray direction is pointing away from object
    contactPoint = gameObject.rect.pos + hitNear * rayDir;

    if (tNear.x > tNear.y)
    {
        if (invDir.x < 0)
            contactNormal = {1, 0};
        else
            contactNormal = {-1, 0};
    }
    else if (tNear.x < tNear.y)
    {
        if (invDir.y < 0)
            contactNormal = {0, 1};
        else
            contactNormal = {0, -1};
    }

    return true;
}

void PlayerPhysicsComponent::AABB(GameObject &gameObject)
{
    for (const auto &obj : m_world)
    {
        if (gameObject.ID != obj->ID)
        {
        }
    }
}

} // namespace smb