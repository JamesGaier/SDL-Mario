#include "StaticTileGraphicsComponent.hpp"
#include "ResourceFactory.hpp"

namespace smb
{

StaticTileGraphicsComponent::StaticTileGraphicsComponent(TileColor color, math::Vec2f pos, SDL_Renderer *renderer, float &cameraX)
    : m_renderer{renderer},
    m_cameraX{cameraX}
{
    auto resource = ResourceFactory::getResource("static_assets");
    m_tile = resource->coords[static_cast<unsigned>(color)];
    m_scaleRect.size.x = m_size;
    m_scaleRect.size.y = m_size;
    m_scaleRect.pos.x = pos.x;
    m_scaleRect.pos.y = pos.y;
    m_spritesheet = resource->texture;
}

void StaticTileGraphicsComponent::render(GameObject &gameObject)
{
    auto renderBox = gameObject.getRenderBox();
    renderBox.pos.x -= m_cameraX;
    m_imageRenderer.render(m_renderer, m_spritesheet, m_tile, renderBox);
}

} // namespace smb
