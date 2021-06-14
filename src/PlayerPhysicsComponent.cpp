#include "PlayerPhysicsComponent.hpp"

namespace smb
{

void PlayerPhysicsComponent::update(GameObject &gameObject, float dt)
{
    std::lock_guard<std::mutex> lg{m_updateMutex};
    gameObject.m_velocity.x += gameObject.m_acceleration.x * dt;
    gameObject.m_velocity.y += gameObject.m_acceleration.y * dt;
    gameObject.m_position.x += gameObject.m_velocity.x * dt + gameObject.m_acceleration.x * dt * dt;
}

} // namespace smb