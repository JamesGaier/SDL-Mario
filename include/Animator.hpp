#pragma once
#include "ImageRenderer.hpp"
#include "Util.hpp"
#include <SDL.h>
#include <map>
#include <string>
#include <vector>

namespace smb
{

class Animator
{
  public:

    ~Animator() = default;

    Animator(const Animator &animator);


    Animator(SDL_Renderer *renderer, const std::string &spriteFileName, const std::string &coordsFileName);

    void addAnimation(const std::string &name, unsigned begin, unsigned end);

    void setAnimation(const std::string &name);

    void renderAnimation(math::Rect &scaleRect);

    SDL_Texture *getSpriteSheet() const
    {
        return m_spritesheet;
    }

    std::vector<SDL_Rect> getFrames() const
    {
        return m_frames;

    }

    SDL_Renderer *getRenderer() const
    {
        return m_renderer;
    }

  private:
    ImageRenderer m_imageRenderer;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_spritesheet;
    std::vector<SDL_Rect> m_frames;
    std::map<std::string, std::pair<unsigned, unsigned>> m_animations;
    std::string m_currentAnimation;
    const unsigned speed{8};
    int m_currentFrame{-1};
};

} // namespace smb
