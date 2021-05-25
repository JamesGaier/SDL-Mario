#pragma once
#include <SDL.h>
#include <array>
#include <vector>

namespace smb
{
template <typename T> struct Vec2
{
    T x, y;
};

template <typename T> struct Rect
{
    std::array<Vec2<T>, 4> m_verts;
};

std::string read_file(const std::string &path);

std::vector<SDL_Rect> parse_coords(const std::string &coords);

} // namespace smb
