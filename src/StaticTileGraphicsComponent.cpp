#include "StaticTileGraphicsComponent.hpp"
#include <iostream>

namespace smb
{

StaticTileGraphicsComponent::StaticTileGraphicsComponent(TileColor color, math::Vec2f pos, SDL_Renderer *renderer)
    : m_renderer{renderer}
{
    auto tilesStr = read_file("textCoordsStatic.txt");
    auto tiles = parse_spritesheet(tilesStr);
    m_tile = tiles[static_cast<unsigned>(color)];
    m_scaleRect.w = m_size;
    m_scaleRect.h = m_size;
    m_scaleRect.x = pos.x;
    m_scaleRect.y = pos.y;
}

void StaticTileGraphicsComponent::render(GameObject &)
{
    if (m_spriteSheet == nullptr)
    {
        m_spriteSheet = loadImage(toAbsolute("tiles.png"), m_renderer);
    }

    SDL_RenderCopy(m_renderer, m_spriteSheet, &m_tile, &m_scaleRect);
}

} // namespace smb
