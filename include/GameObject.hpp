#pragma once
#include "GraphicsComponent.hpp"
#include "InputComponent.hpp"
#include "Math.hpp"
#include "PhysicsComponent.hpp"
#include <SDL.h>
#include <memory>
#include <vector>
#include <mutex>

namespace smb
{

class GraphicsComponent;
class PhysicsComponent;
class InputComponent;
class GameObject
{
  public:
    unsigned long ID;

    GameObject(std::unique_ptr<GraphicsComponent> graphicsComponent, std::unique_ptr<PhysicsComponent> physicsComponent,
               std::unique_ptr<InputComponent> inputComponent, math::Rect scaleRect);

    void update(float dt);
    void render();

    float getPositionX() const;
    void setPositionX(float x);

    float getPositionY() const;
    void setPositionY(float y);

    float getVelocityX() const;
    void setVelocityX(float x);

    float getVelocityY() const;
    void setVelocityY(float y);

    float getAccelerationX() const;
    void setAccelerationX(float x);

    float getAccelerationY() const;
    void setAccelerationY(float y);

    math::Rect getBoundingBox();
    void setBoundingBox(const math::Rect &rect);

    float getBoundingBoxSizeX() const; 
    float getBoundingBoxSizeY() const; 

    float getRenderBoxSizeX() const; 
    float getRenderBoxSizeY() const; 

    math::Rect getRenderBox();
    void setRenderBox(const math::Rect &rect);

  private:
    math::Rect m_renderBox;
    std::unique_ptr<GraphicsComponent> m_graphicsComponent;
    std::unique_ptr<PhysicsComponent> m_physicsComponent;
    std::unique_ptr<InputComponent> m_inputComponent;
    std::mutex m_mutex;
    math::Vec2f m_position;
    math::Vec2f m_velocity;
    math::Vec2f m_acceleration;
    math::Rect m_boundingBox;
};

} // namespace smb
