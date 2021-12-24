#pragma once
#include "Math.hpp"
#include <SDL.h>
#include <mutex>

namespace smb
{

class ImageRenderer
{
  public:
    void render(SDL_Renderer *renderer, SDL_Texture *tex,const SDL_Rect &frame,const math::Rect &rect)
    {
        {
            std::lock_guard<std::mutex> lg{m_updateMutex};
            m_wrapper = SDL_Rect{static_cast<int>(rect.pos.x), static_cast<int>(rect.pos.y),
                                 static_cast<int>(rect.size.x), static_cast<int>(rect.size.y)};
        }

        SDL_RenderCopy(renderer, tex, &frame, &m_wrapper);
    }

  private:
    SDL_Rect m_wrapper;
    std::mutex m_updateMutex;
};

} // namespace smb
