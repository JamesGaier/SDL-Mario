#pragma once

#include "GameObject.hpp"
#include "GraphicsComponent.hpp"
#include "ImageRenderer.hpp"
#include <SDL.h>
#include <mutex>
#include <vector>

namespace smb
{

class PlayerGraphicsComponent : public GraphicsComponent
{
  public:
    PlayerGraphicsComponent();

    ~PlayerGraphicsComponent() = default;

    void render(GameObject &gameObject, SDL_Renderer *renderer) override;

  private:
    std::vector<SDL_Rect> m_frames;
    ImageRenderer m_renderer;
    SDL_Texture *m_spriteSheet{nullptr};
    const unsigned tempFrame = 14;
    const unsigned m_width{32};
    const unsigned m_height{64};
    std::mutex m_renderMutex;
};

} // namespace smb