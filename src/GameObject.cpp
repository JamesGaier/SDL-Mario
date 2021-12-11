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
    : renderBox{scaleRect}, m_graphicsComponent{std::move(graphicsComponent)},
      m_physicsComponent{std::move(physicsComponent)}, m_inputComponent{std::move(inputComponent)}
{
    boundingBox.pos.x = renderBox.pos.x;
    boundingBox.pos.y = renderBox.pos.y;
    boundingBox.size.x = renderBox.size.x;
    boundingBox.size.y = renderBox.size.y;

    ID = math::generateRandomInt(1, 100);
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
} // namespace smb
