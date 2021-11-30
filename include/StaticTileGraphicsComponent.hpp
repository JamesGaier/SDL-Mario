#include "GraphicsComponent.hpp"
#include "Math.hpp"
#include "Util.hpp"
#include <SDL.h>

namespace smb
{

class StaticTileGraphicsComponent : public GraphicsComponent
{
  public:
    StaticTileGraphicsComponent(TileColor tileColor, math::Vec2f pos);

    ~StaticTileGraphicsComponent() override = default;

    void render(GameObject &gameObject, SDL_Renderer *renderer);

  private:
    SDL_Rect m_tile;
    SDL_Rect m_scaleRect;
    SDL_Texture *m_spriteSheet{nullptr};
    const unsigned m_size{32};
};
} // namespace smb