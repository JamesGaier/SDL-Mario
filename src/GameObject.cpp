#include "GameObject.hpp"
#include "Math.hpp"
#include <SDL.h>
#include <iostream>
#include <mutex>


namespace smb
{

GameObject::GameObject(std::unique_ptr<GraphicsComponent> graphicsComponent,
                       std::unique_ptr<PhysicsComponent> physicsComponent,
                       std::unique_ptr<InputComponent> inputComponent, math::Rect scaleRect)
    : m_renderBox{scaleRect}, m_graphicsComponent{std::move(graphicsComponent)},
      m_physicsComponent{std::move(physicsComponent)}, m_inputComponent{std::move(inputComponent)}
{
    m_boundingBox.pos = m_renderBox.pos;
    m_boundingBox.size = m_renderBox.size;
    m_position = m_boundingBox.pos;
}

void GameObject::update(float dt)
{
    std::lock_guard<std::mutex> lg{m_mutex};
    m_inputComponent->update(*this);
    m_physicsComponent->update(*this, dt);
}

void GameObject::render()
{
    std::lock_guard<std::mutex> lg{m_mutex};
    m_graphicsComponent->render(*this);
}

float GameObject::getPositionX() const
{
    return m_position.x; 
}

void GameObject::setPositionX(float x)
{
    m_position.x = x;
    m_boundingBox.pos.x = x;
    m_renderBox.pos.x = x;
}

float GameObject::getPositionY() const
{
    return m_position.y; 
}

void GameObject::setPositionY(float y)
{
    m_position.y = y;
    m_boundingBox.pos.y = y;
    m_renderBox.pos.y = y;
}

float GameObject::getVelocityX() const
{
    return m_velocity.x;
}

void GameObject::setVelocityX(float x)
{
    m_velocity.x = x;
}

float GameObject::getVelocityY() const
{
    return m_velocity.y;
}

void GameObject::setVelocityY(float y)
{
    m_velocity.y = y;
}

float GameObject::getAccelerationX() const
{
    return m_acceleration.x;
}

void GameObject::setAccelerationX(float x)
{
    m_acceleration.x = x;
}

float GameObject::getAccelerationY() const
{
    return m_acceleration.y;
}

void GameObject::setAccelerationY(float y)
{
    m_acceleration.y = y;
}

math::Rect GameObject::getBoundingBox()
{
    return m_boundingBox;
}

void GameObject::setBoundingBox(const math::Rect &rect)
{
    m_boundingBox = rect;
}

math::Rect GameObject::getRenderBox() 
{
    return m_renderBox;
}

void GameObject::setRenderBox(const math::Rect &rect)
{
    m_renderBox = rect;
}

float GameObject::getBoundingBoxSizeX() const
{
    return m_boundingBox.size.x;
}

float GameObject::getBoundingBoxSizeY() const
{
    return m_boundingBox.size.y;
}


float GameObject::getRenderBoxSizeX() const
{
    return m_renderBox.size.x;
}

float GameObject::getRenderBoxSizeY() const
{
    return m_renderBox.size.y;
}

} // namespace smb
