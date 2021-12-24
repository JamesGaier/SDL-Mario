#pragma once
#include "GameObject.hpp"
#include "Camera.hpp"
#include <SDL.h>

namespace smb
{

class GameObject;
class GraphicsComponent
{
  public:
    virtual ~GraphicsComponent() = default;
    virtual void render(GameObject &gameObject) = 0;
};

} // namespace smb
