#pragma once
#include "Util.hpp"

namespace smb
{
    class Renderable
    {
    public:
        virtual void render(float dt) = 0;
    private:
        Vec2<float> m_position;
        bool m_isSolid;
    };
}