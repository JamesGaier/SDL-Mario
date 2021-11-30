#pragma once
#include "GraphicsComponent.hpp"
#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "Util.hpp"
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
    Vec2f pos;
    Vec2f vel;
    Vec2f accel;
    Rect boundingBox;
    Rect renderBox;
    unsigned long ID;

    GameObject(std::unique_ptr<GraphicsComponent> graphicsComponent, std::unique_ptr<PhysicsComponent> physicsComponent,
               std::unique_ptr<InputComponent> inputComponent, unsigned long ID, Rect scaleRect);

    void update(float dt);
    void render(SDL_Renderer *renderer);

  private:
    std::unique_ptr<GraphicsComponent> m_graphicsComponent;
    std::unique_ptr<PhysicsComponent> m_physicsComponent;
    std::unique_ptr<InputComponent> m_inputComponent;
};

} // namespace smb
