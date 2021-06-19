#pragma once
#include "Renderable.hpp"
#include <SDL.h>
#include <array>
#include <memory>
#include <vector>

namespace smb
{

enum class TileType
{
    GROUND = 1,
    PLAYER,
    BREAKABLE,
    UP_PIPE,
    LEFT_PIPE,
    RIGHT_PIPE,
    DOWN_PIPE,
    MUSHROOM,
    QUESTION,
    INVISIBLE,
    SOLID,
    FLAG_POLE,
    CASTLE
};

enum class TileColor
{
    BROWN,
    BLUE,
    WHITE,
    GREEN
};

template <typename T> struct Vec2
{
    T x, y;

    Vec2() : x{0}, y{0}
    {
    }

    Vec2(T x, T y) : x{x}, y{y}
    {
    }

    Vec2<T> operator+(Vec2<T> &&rhs)
    {
        return {x + rhs.x, y + rhs.y};
    }

    Vec2<T> operator+=(Vec2<T> &&rhs)
    {
        return {x + rhs.x, y + rhs.y};
    }

    Vec2<T> operator-(Vec2<T> &&rhs)
    {
        return {x - rhs.x, y - rhs.y};
    }

    // dot product
    T operator*(Vec2<T> &&rhs)
    {
        return (x + rhs.x) * (y + rhs.y);
    }
    
    Vec2<T> operator*(T rhs)
    {
        return {rhs * x, rhs * y};
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
