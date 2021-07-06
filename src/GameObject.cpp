#include "GameObject.hpp"
#include <SDL.h>
#include <iostream>

namespace smb
{

GameObject::GameObject(std::unique_ptr<GraphicsComponent> graphicsComponent,
                       std::unique_ptr<PhysicsComponent> physicsComponent,
                       std::unique_ptr<InputComponent> inputComponent, unsigned long OBJECT_ID, Rect scaleRect)
    : m_graphicsComponent{std::move(graphicsComponent)}, m_physicsComponent{std::move(physicsComponent)},
      m_inputComponent{std::move(inputComponent)}, ID{OBJECT_ID}, rect{scaleRect}
{
}

void GameObject::update(float dt)
{
    m_inputComponent->update(*this);
    m_physicsComponent->update(*this, dt);
}

void GameObject::render(SDL_Renderer *renderer)
{
    m_graphicsComponent->render(*this, renderer);
}
} // namespace smb