#include "StaticTileGraphicsComponent.hpp"
#include "ResourceFactory.hpp"
#include <iostream>

namespace smb
{

StaticTileGraphicsComponent::StaticTileGraphicsComponent(TileColor color, math::Vec2f pos, SDL_Renderer *renderer)
    : m_renderer{renderer}
{
    auto resource = ResourceFactory::getResource("static_assets");
    m_tile = resource->coords[static_cast<unsigned>(color)];
    m_scaleRect.w = m_size;
    m_scaleRect.h = m_size;
    m_scaleRect.x = pos.x;
    m_scaleRect.y = pos.y;
    m_spriteSheet = resource->texture;
}

void StaticTileGraphicsComponent::render(GameObject &)
{
    SDL_RenderCopy(m_renderer, m_spriteSheet, &m_tile, &m_scaleRect);
}

} // namespace smb
