#pragma once
#include <SDL.h>

namespace smb
{
class Renderable
{
  public:
    virtual ~Renderable() = default;
    virtual void render(float dt, SDL_Renderer *renderer) = 0;
};
} // namespace smb