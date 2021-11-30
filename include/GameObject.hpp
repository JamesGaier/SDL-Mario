#pragma once
#include "GraphicsComponent.hpp"
#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "Math.hpp"
#include <SDL.h>
#include <memory>
#include <vector>

namespace smb
{

class GraphicsComponent;
class PhysicsComponent;
class InputComponent;
class GameObject
{
  public:
    math::Vec2f pos;
    math::Vec2f vel;
    math::Vec2f accel;
    math::Rect boundingBox;
    math::Rect renderBox;
    unsigned long ID;

    GameObject(std::unique_ptr<GraphicsComponent> graphicsComponent, std::unique_ptr<PhysicsComponent> physicsComponent,
               std::unique_ptr<InputComponent> inputComponent, unsigned long ID, math::Rect scaleRect);

    void update(float dt);
    void render(SDL_Renderer *renderer);

  private:
    std::unique_ptr<GraphicsComponent> m_graphicsComponent;
    std::unique_ptr<PhysicsComponent> m_physicsComponent;
    std::unique_ptr<InputComponent> m_inputComponent;
};

} // namespace smb
