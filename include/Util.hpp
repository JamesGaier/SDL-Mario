#pragma once
#include "Renderable.hpp"
#include <SDL.h>
#include <array>
#include <memory>
#include <vector>

namespace smb
{
template <typename T> struct Vec2
{
    T x, y;

    Vec2() : x{0}, y{0}
    {
    }

    Vec2(T x, T y) : x{x}, y{y}
    {
    }

    Vec2(const Vec2 &copy) : x{copy.x}, y{copy.y}
    {
    }

    Vec2<T> &operator+(const Vec2 &rhs)
    {
        return {x + rhs.x, y + rhs.y};
    }

    Vec2<T> &operator+=(const Vec2 &rhs)
    {
        return {x + rhs.x, y + rhs.y};
    }

    Vec2<T> &operator-(const Vec2 &rhs)
    {
        return {x - rhs.x, y - rhs.y};
    }

    // dot product
    T operator*(const Vec2 &rhs)
    {
        return (x + rhs.x) * (y + rhs.y);
    }
};

template <typename T> struct Rect
{
    std::array<Vec2<T>, 4> m_verts;
};

std::string read_file(const std::string &path);

std::string toAbsolute(const std::string &path, const std::string &parent = "../res");

std::vector<int> parse_coords(const std::string &coords);

std::vector<std::vector<int>> parse_level(const std::string &coords);

std::vector<SDL_Rect> parse_spritesheet(const std::string &coords);

void loadImage(const std::string &path, SDL_Renderer *renderer, SDL_Texture **texture);

} // namespace smb
