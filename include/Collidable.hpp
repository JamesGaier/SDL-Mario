#pragma once
#include "Util.hpp"

namespace smb
{

    class Collidable
    {
    public:
        virtual ~Collidable() = default;
        virtual void update(float dt) = 0;
    private:
        Rect<float> m_boundBox;
    };

}