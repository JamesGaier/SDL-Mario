#include "StaticTileGraphicsComponent.hpp"
#include "Util.hpp"
#include <iostream>

namespace smb
{

StaticTileGraphicsComponent::StaticTileGraphicsComponent(TileColor color, Vec2<float> pos)
{
    auto tilesStr = read_file("textCoordsStatic.txt");
    auto tiles = parse_spritesheet(tilesStr);
    m_tile = tiles[static_cast<unsigned>(color)];
    m_scaleRect.w = m_size;
    m_scaleRect.h = m_size;
    m_scaleRect.x = pos.x;
    m_scaleRect.y = pos.y;
}

void StaticTileGraphicsComponent::render(GameObject &gameObject, SDL_Renderer *renderer)
{
    if (m_spriteSheet == nullptr)
    {
        m_spriteSheet = loadImage(toAbsolute("tiles.png"), renderer);
    }

    SDL_RenderCopy(renderer, m_spriteSheet, &m_tile, &m_scaleRect);
}

} // namespace smb