#pragma once
#include "GraphicsComponent.hpp"
#include "ImageRenderer.hpp"
#include "Math.hpp"
#include "Util.hpp"
#include <SDL.h>

namespace smb
{

class StaticTileGraphicsComponent : public GraphicsComponent
{
  public:
    StaticTileGraphicsComponent(TileColor tileColor, math::Vec2f pos, SDL_Renderer *renderer, float &cameraX);

    ~StaticTileGraphicsComponent() override = default;

    void render(GameObject &gameObject) override;

  private:
    ImageRenderer m_imageRenderer;
    SDL_Rect m_tile;
    math::Rect m_scaleRect;
    SDL_Texture *m_spritesheet;
    SDL_Renderer *m_renderer;
    const unsigned m_size{32};
    float &m_cameraX;
};
} // namespace smb
