#include "PlayerPhysicsComponent.hpp"
#include <algorithm>
#include <iostream>

namespace smb
{

PlayerPhysicsComponent::PlayerPhysicsComponent(std::vector<std::unique_ptr<GameObject>> &world) : m_world{world}
{
}

void PlayerPhysicsComponent::update(GameObject &gameObject, float dt)
{
    std::lock_guard<std::mutex> lg{m_updateMutex};
    gameObject.m_velocity += gameObject.m_acceleration * dt;
    gameObject.m_position += gameObject.m_velocity * dt;
    AABB(gameObject);
}

void PlayerPhysicsComponent::AABB(GameObject &gameObject)
{
    
    for(const auto &obj : m_world)
    {
        if (gameObject.ID != obj->ID)
        {
            if(gameObject.m_scaleRect.y + gameObject.m_scaleRect.h > obj->m_scaleRect.y
            && gameObject.m_scaleRect.x >= obj->m_scaleRect.x
            && gameObject.m_scaleRect.x + gameObject.m_scaleRect.w <= obj->m_scaleRect.x + obj->m_scaleRect.w)
            {
                gameObject.m_scaleRect.y = obj->m_scaleRect.y - gameObject.m_scaleRect.h;
                gameObject.m_position.y = gameObject.m_scaleRect.y;
                gameObject.m_velocity.y = 0;
                gameObject.m_acceleration.y = 0;
            }
        }
    }
}

} // namespace smb