#pragma once
#include "GraphicsComponent.hpp"
#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "Util.hpp"
#include <SDL.h>
#include <memory>

namespace smb
{

class GraphicsComponent;
class PhysicsComponent;
class InputComponent;
class GameObject
{
  public:
    Vec2<float> m_position;
    Vec2<float> m_velocity;
    Vec2<float> m_acceleration;

    GameObject(std::unique_ptr<GraphicsComponent> &graphicsComponent,
               std::unique_ptr<PhysicsComponent> &physicsComponent, std::unique_ptr<InputComponent> &inputComponent);

    void update(float dt);
    void render(SDL_Renderer *renderer);

  private:
    std::unique_ptr<GraphicsComponent> m_graphicsComponent;
    std::unique_ptr<PhysicsComponent> m_physicsComponent;
    std::unique_ptr<InputComponent> m_inputComponent;
};

} // namespace smb