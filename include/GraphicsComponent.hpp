#pragma once
#include "GameObject.hpp"
#include <SDL.h>

namespace smb
{

class GameObject;
class GraphicsComponent 
{
  public:
    virtual ~GraphicsComponent() = default;
    virtual void render(GameObject &gameObject, SDL_Renderer *renderer) = 0;
};

} // namespace smb