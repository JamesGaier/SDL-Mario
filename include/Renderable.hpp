#pragma once
#include "Util.hpp"
#include <SDL_image.h>

namespace smb
{
    class Renderable
    {
    public:
        virtual ~Renderable() = default;
        virtual void render(float dt, SDL_Surface* screenSurface) = 0;
    private:
        Vec2<float> m_position;
        bool m_isSolid;
    };
}