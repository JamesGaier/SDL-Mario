#include "PlayerGraphicsComponent.hpp"
#include "Util.hpp"

namespace smb
{

PlayerGraphicsComponent::PlayerGraphicsComponent()
{
    const auto coords_f = read_file("textCoords.txt");
    auto coords = parse_spritesheet(coords_f);
    m_frames = std::move(coords);
}

void PlayerGraphicsComponent::render(GameObject &gameObject, SDL_Renderer *renderer)
{
    if (m_spriteSheet == nullptr)
    {
        m_spriteSheet = loadImage(toAbsolute("characters.gif"), renderer);
    }

    m_renderer.render(renderer, m_spriteSheet, m_frames[tempFrame], gameObject.rect);
}

} // namespace smb