#include "PlayerPhysicsComponent.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace smb
{

PlayerPhysicsComponent::PlayerPhysicsComponent(std::vector<std::unique_ptr<GameObject>> &world, Camera &camera) : m_world{world}, m_camera{camera}
{
}

void PlayerPhysicsComponent::update(GameObject &gameObject, float dt)
{
    std::lock_guard<std::mutex> lg{m_updateMutex};
    move(gameObject, dt);
}

bool intersects(const math::Rect &lhs, const math::Rect &rhs)
{
    return lhs.pos.x < rhs.pos.x + rhs.size.x && lhs.pos.x + lhs.size.x > rhs.pos.x &&
           lhs.pos.y < rhs.pos.y + rhs.size.y && lhs.pos.y + lhs.size.y > rhs.pos.y;
}

GameObject *PlayerPhysicsComponent::checkCollision(GameObject &go)
{
    for (const auto &obj : m_world)
    {
        if (go.ID != obj->ID && intersects(go.getBoundingBox(), obj->getBoundingBox()))
        {
            return obj.get();
        }
    }

    return nullptr;
}

void PlayerPhysicsComponent::move(GameObject &go, const float dt)
{
    m_camera.update(go);
    go.setVelocityX(go.getVelocityX() + go.getAccelerationX() * dt);
    go.setPositionX(go.getPositionX() + go.getVelocityX() * dt + 0.5f * go.getAccelerationX() * dt * dt);
    auto collisionObjectX = checkCollision(go);
    if (collisionObjectX != nullptr)
    {
        auto objectPositionX = collisionObjectX->getPositionX();
        auto playerSizeX = go.getBoundingBoxSizeX();
        if (go.getVelocityX() > 0)
        {
            go.setPositionX(objectPositionX - playerSizeX);
            go.setVelocityX(0);
        }
        else if (go.getVelocityX() < 0)
        {
            auto boundingBox = collisionObjectX->getBoundingBox();
            auto objectSizeX = boundingBox.size.x;

            go.setPositionX(objectPositionX + objectSizeX);
            go.setVelocityX(0);
        }
    }

    go.setVelocityY(go.getVelocityY() + go.getAccelerationY() * dt);
    go.setPositionY(go.getPositionY() + go.getVelocityY() * dt + 0.5 * go.getAccelerationY() * dt * dt);
    auto collisionObjectY = checkCollision(go);
    if (collisionObjectY != nullptr)
    {
        auto objectPositionY = collisionObjectY->getPositionY();
        auto playerSizeY = go.getBoundingBoxSizeY();
        if (go.getVelocityY() > 0)
        {
            go.setPositionY(objectPositionY - playerSizeY);
            go.setVelocityY(0);
            m_onGround = true;
        }
        else if (go.getVelocityY() < 0)
        {
            auto objectSizeY = collisionObjectY->getBoundingBoxSizeY();
            go.setPositionY(objectPositionY + objectSizeY);
            go.setVelocityY(0);
        }
    }
    else
    {
        m_onGround = false;
    }
}

bool PlayerPhysicsComponent::onGround() const
{
    return m_onGround;
}

void PlayerPhysicsComponent::setOnGround(bool onGround)
{
    m_onGround = onGround;
}

} // namespace smb
