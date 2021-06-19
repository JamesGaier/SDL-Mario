#include "PlayerPhysicsComponent.hpp"
#include <algorithm>
#include <iostream>

namespace smb
{

void PlayerPhysicsComponent::update(GameObject &gameObject, float dt)
{
    std::lock_guard<std::mutex> lg{m_updateMutex};
    gameObject.m_velocity += gameObject.m_acceleration * dt;
    gameObject.m_position += gameObject.m_velocity * dt;
}

} // namespace smb