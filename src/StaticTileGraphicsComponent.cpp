#include "StaticTileGraphicsComponent.hpp"
#include "Util.hpp"

namespace smb
{
	
StaticTileGraphicsComponent::StaticTileGraphicsComponent(TileType type)
{
    auto tilesStr = read_file("textCoordsStatic.txt");
    auto tiles = parse_spritesheet(tilesStr);
	m_tile = tiles[static_cast<unsigned>(type)];
}

void StaticTileGraphicsComponent::render(GameObject &gameObject, SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, m_spriteSheet, &m_tile, &m_scaleRect);
}

}