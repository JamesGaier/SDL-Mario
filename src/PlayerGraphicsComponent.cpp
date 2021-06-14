#include "PlayerGraphicsComponent.hpp"
#include "Util.hpp"

namespace smb
{

PlayerGraphicsComponent::PlayerGraphicsComponent(std::vector<SDL_Rect> &frames, SDL_Texture *spriteSheet,
                                                 SDL_Renderer *renderer)
    : m_frames{frames}, m_spriteSheet{spriteSheet}
{
    if (m_spriteSheet == NULL)
    {
        loadImage(toAbsolute("characters.gif"), renderer, &m_spriteSheet);
    }
}

void PlayerGraphicsComponent::render(GameObject &gameObject, SDL_Renderer *renderer)
{
    {
        std::lock_guard<std::mutex> lg{m_renderMutex};
        m_scaleRect.x = static_cast<int>(gameObject.m_position.x);
        m_scaleRect.y = static_cast<int>(gameObject.m_position.y);
    }
    SDL_RenderCopy(renderer, m_spriteSheet, &m_frames[tempFrame], &m_scaleRect);
}

} // namespace smb