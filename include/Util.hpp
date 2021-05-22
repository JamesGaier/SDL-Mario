#pragma once
#include <iostream>
#include <array>

namespace smb
{
    template<typename T>
    struct Vec2
    {
        T x, y;
    };


    template<typename T>
    struct Rect
    {
        std::array<Vec2<T>, 4> m_verts;
    };

}