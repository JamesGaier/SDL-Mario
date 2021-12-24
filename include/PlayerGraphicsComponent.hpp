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
    PlayerGraphicsComponent(SDL_Renderer *renderer, float &cameraX);

    ~PlayerGraphicsComponent() = default;

    void render(GameObject &gameObject) override;

    Animator &getAnimator();

  private:
    std::vector<SDL_Rect> m_frames;
    ImageRenderer m_imageRenderer;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_spritesheet;
    Animator m_animator;
    const unsigned m_width{32};
    const unsigned m_height{64};
    float &m_cameraX;
    std::mutex m_renderMutex;

    void loadPlayerAnimations();

};

} // namespace smb
