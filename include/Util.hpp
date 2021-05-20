#pragma once
#include <iostream>
#include <array>

namespace smb
{

    void dynamic_assert(bool expr, const std::string& msg)
    {
        if(expr)
        {
            std::cout << msg << std::endl;
        }
        else
        {
            std::cerr << "Assertion Failed" << std::endl;
            std::abort();
        }
    }

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