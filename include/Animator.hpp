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

    Animator(SDL_Renderer *renderer);

    void addAnimation(const std::string &name, unsigned begin, unsigned end);

    void setAnimation(const std::string &name);

    void renderAnimation();

    SDL_Rect getFrame() const
    {
        return m_frames.at(m_currentFrame / speed);
    }

  private:
    SDL_Renderer *m_renderer;
    SDL_Texture *m_spritesheet;
    std::vector<SDL_Rect> m_frames;
    std::map<std::string, std::pair<unsigned, unsigned>> m_animations;
    std::string m_currentAnimation;
    const unsigned speed{8};
    int m_currentFrame{-1};
};

} // namespace smb
