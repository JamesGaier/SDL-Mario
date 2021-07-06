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
    AABB(gameObject, dt);
}

bool intersects(const Rect &lhs, const Rect &rhs)
{
    return lhs.pos.x < rhs.pos.x + rhs.size.x
        && lhs.pos.x + lhs.size.x > rhs.pos.x
        && lhs.pos.y < rhs.pos.y + rhs.size.y
        && lhs.pos.y + lhs.size.y > rhs.pos.y; 
            
}

void PlayerPhysicsComponent::AABB(GameObject &gameObject, const float dt)
{
    auto &rect = gameObject.rect; 
    rect.velocity.x += rect.acceleration.x * dt;
    rect.pos.x += rect.velocity.x * dt;
    
    for (const auto &obj : m_world)
    {
        if (gameObject.ID != obj->ID && intersects(gameObject.rect, obj->rect))
        {
            if(gameObject.rect.velocity.x > 0)
            {
               gameObject.rect.pos.x = obj->rect.pos.x - gameObject.rect.size.x; 
               gameObject.rect.velocity.x = 0;
            }
            else if(gameObject.rect.velocity.x < 0)
            {
               gameObject.rect.pos.x = obj->rect.pos.x + obj->rect.size.x; 
               gameObject.rect.velocity.x = 0;
            }
            
        }
    }

    rect.velocity.y += rect.acceleration.y * dt;
    rect.pos.y += rect.velocity.y * dt;

    for (const auto &obj : m_world)
    {
        if (gameObject.ID != obj->ID && intersects(gameObject.rect, obj->rect))
        {
            if(gameObject.rect.velocity.y > 0)
            {
                gameObject.rect.pos.y = obj->rect.pos.y - gameObject.rect.size.y;
                gameObject.rect.velocity.y = 0;
            }
            else if(gameObject.rect.velocity.y < 0)
            {
                gameObject.rect.pos.y = obj->rect.pos.y + obj->rect.size.y;
                gameObject.rect.velocity.y = 0;
            }
        }
    }
}

} // namespace smb