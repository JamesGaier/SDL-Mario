#pragma once

#include "GameObject.hpp"
#include "GraphicsComponent.hpp"
#include <SDL.h>
#include <vector>

namespace smb
{

class PlayerGraphicsComponent : public GraphicsComponent
{
  public:
    PlayerGraphicsComponent(std::vector<SDL_Rect> &frames, SDL_Texture *spriteSheet, SDL_Renderer *renderer);

    ~PlayerGraphicsComponent() = default;

    void render(GameObject &gameObject, SDL_Renderer *renderer) override;

  private:
    std::vector<SDL_Rect> m_frames;
    SDL_Texture *m_spriteSheet;
    SDL_Rect m_scaleRect;
    const unsigned tempFrame = 14;
};

} // namespace smb