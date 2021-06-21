#include "GameObject.hpp"
#include <SDL.h>

namespace smb
{

GameObject::GameObject(std::unique_ptr<GraphicsComponent> graphicsComponent,
                       std::unique_ptr<PhysicsComponent> physicsComponent,
                       std::unique_ptr<InputComponent> inputComponent,
                       unsigned long OBJECT_ID,
                       SDL_Rect scaleRect)
    : m_graphicsComponent{std::move(graphicsComponent)}, m_physicsComponent{std::move(physicsComponent)},
      m_inputComponent{std::move(inputComponent)}, ID{OBJECT_ID}, m_scaleRect{scaleRect}
{
    m_position.x = m_scaleRect.x;
    m_position.y = m_scaleRect.y;
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