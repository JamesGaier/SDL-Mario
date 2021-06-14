#include "GraphicsComponent.hpp"
#include <SDL.h>

namespace smb
{
enum class TileColor
{
    BROWN,
    BLUE,
    WHITE,
    GREEN
};


class StaticTileGraphicsComponent : public GraphicsComponent
{
public:

	StaticTileGraphicsComponent();

    ~StaticTileGraphicsComponent() override = default;

    void render(GameObject &gameObject, SDL_Renderer *renderer);
private:
	SDL_Rect m_tile;
	SDL_Rect m_scaleRect;
	SDL_Texture *m_spriteSheet;
};
} // namespace smb