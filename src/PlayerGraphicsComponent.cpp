#include "PlayerGraphicsComponent.hpp"
#include "Util.hpp"
#include <iostream>

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
    if (m_spriteSheet == nullptr) // NULL -> nullptr
    {
        m_spriteSheet = loadImage(toAbsolute("characters.gif"), renderer);
    }

    {
        std::lock_guard<std::mutex> lg{m_renderMutex};
        gameObject.m_scaleRect.x = static_cast<int>(gameObject.m_position.x);
        gameObject.m_scaleRect.y = static_cast<int>(gameObject.m_position.y);
    } // convert vector data into SDL_Rect to function if multiple uses occur

    SDL_RenderCopy(renderer, m_spriteSheet, &m_frames[tempFrame], &gameObject.m_scaleRect);
}

} // namespace smb