#pragma once

#include "Animator.hpp"
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
    PlayerGraphicsComponent(SDL_Renderer *renderer);

    ~PlayerGraphicsComponent() = default;

    void render(GameObject &gameObject) override;

    Animator &getAnimator();

  private:
    void loadPlayerAnimations();

    std::vector<SDL_Rect> m_frames;
    ImageRenderer m_imageRenderer;
    SDL_Renderer *m_renderer;
    Animator m_animator;
    SDL_Texture *m_spriteSheet{nullptr};
    unsigned tempFrame = 160;
    const unsigned m_width{32};
    const unsigned m_height{64};
    std::mutex m_renderMutex;
};

} // namespace smb
