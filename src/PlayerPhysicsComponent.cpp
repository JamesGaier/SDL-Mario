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
    move(gameObject, dt);
}

bool intersects(const math::Rect &lhs, const math::Rect &rhs)
{
    return lhs.pos.x < rhs.pos.x + rhs.size.x && lhs.pos.x + lhs.size.x > rhs.pos.x &&
           lhs.pos.y < rhs.pos.y + rhs.size.y && lhs.pos.y + lhs.size.y > rhs.pos.y;
}

GameObject *PlayerPhysicsComponent::checkCollision(const GameObject &go)
{
    for (const auto &obj : m_world)
    {
        if (go.ID != obj->ID && intersects(go.boundingBox, obj->boundingBox))
        {
            return obj.get();
        }
    }

    return nullptr;
}

void PlayerPhysicsComponent::move(GameObject &go, const float dt)
{
    go.vel.x += go.accel.x * dt;
    go.boundingBox.pos.x += go.vel.x * dt + 0.5 * go.accel.x * dt * dt;
    auto collisionObjectX = checkCollision(go);
    if (collisionObjectX != nullptr)
    {
        auto objectPositionX = collisionObjectX->boundingBox.pos.x;

        auto playerSizeX = go.boundingBox.size.x;
        if (go.vel.x > 0)
        {
            go.boundingBox.pos.x = objectPositionX - playerSizeX;
            go.vel.x = 0;
        }
        else if (go.vel.x < 0)
        {
            auto objectSizeX = collisionObjectX->boundingBox.size.x;
            go.boundingBox.pos.x = objectPositionX + objectSizeX;
            go.vel.x = 0;
        }
    }

    go.vel.y += go.accel.y * dt;
    go.boundingBox.pos.y += go.vel.y * dt + 0.5 * go.accel.y * dt * dt;
    auto collisionObjectY = checkCollision(go);
    if (collisionObjectY != nullptr)
    {
        auto objectPositionY = collisionObjectY->boundingBox.pos.y;
        auto playerSizeY = go.boundingBox.size.y;
        if (go.vel.y > 0)
        {
            go.boundingBox.pos.y = objectPositionY - playerSizeY;
            go.vel.y = 0;
            m_onGround = true;
        }
        else if (go.vel.y < 0)
        {
            auto objectSizeY = collisionObjectY->boundingBox.size.y;
            go.boundingBox.pos.y = objectPositionY + objectSizeY;
            go.vel.y = 0;
        }
    }
    else
    {
        m_onGround = false;
    }

    go.renderBox.pos.x = go.boundingBox.pos.x;
    go.renderBox.pos.y = go.boundingBox.pos.y;
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
