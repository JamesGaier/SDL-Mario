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
    move(gameObject, gameObject.ID, dt);
}

bool intersects(const math::Rect &lhs, const math::Rect &rhs)
{
    return lhs.pos.x < rhs.pos.x + rhs.size.x && lhs.pos.x + lhs.size.x > rhs.pos.x &&
           lhs.pos.y < rhs.pos.y + rhs.size.y && lhs.pos.y + lhs.size.y > rhs.pos.y;
}

void PlayerPhysicsComponent::move(GameObject &go, const unsigned long ID, const float dt)
{
    const auto checkCollision = [&](auto &vel, auto &pos, const auto size, const auto xAxis) {
        for (const auto &obj : m_world)
        {
            auto &objPos = xAxis ? obj->renderBox.pos.x : obj->renderBox.pos.y;

            if (ID != obj->ID && intersects(go.renderBox, obj->renderBox))
            {
                if (vel > 0)
                {
                    pos = objPos - size;
                    vel = 0;
                }
                else if (vel < 0)
                {
                    auto objSize = (xAxis) ? obj->renderBox.size.x : obj->renderBox.size.y;
                    go.renderBox.pos.x = objPos + objSize;
                    go.vel.x = 0;
                }
            }
        }
    };

    go.vel.x += go.accel.x * dt;
    go.renderBox.pos.x += go.vel.x * dt + 0.5 * go.accel.x * dt * dt;
    checkCollision(go.vel.x, go.renderBox.pos.x, go.renderBox.size.x, true);

    go.vel.y += go.accel.y * dt;
    go.renderBox.pos.y += go.vel.y * dt + 0.5 * go.accel.y * dt * dt;
    checkCollision(go.vel.y, go.renderBox.pos.y, go.renderBox.size.y, false);
}

} // namespace smb
