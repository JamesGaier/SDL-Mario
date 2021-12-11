#pragma once
#include "GraphicsComponent.hpp"
#include "Math.hpp"
#include "Util.hpp"
#include <SDL.h>

namespace smb
{

class StaticTileGraphicsComponent : public GraphicsComponent
{
  public:
    StaticTileGraphicsComponent(TileColor tileColor, math::Vec2f pos, SDL_Renderer *renderer);

    ~StaticTileGraphicsComponent() override;

    void render(GameObject &gameObject) override;

  private:
    SDL_Rect m_tile;
    SDL_Rect m_scaleRect;
    SDL_Texture *m_spriteSheet{nullptr};
    SDL_Renderer *m_renderer;
    const unsigned m_size{32};
};
} // namespace smb
