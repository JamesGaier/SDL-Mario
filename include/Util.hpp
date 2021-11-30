#pragma once
#include <SDL.h>
#include <array>
#include <memory>
#include <vector>

namespace smb
{

enum class TileType
{
    AIR = 0,
    GROUND = 1,
    SPAWN,
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

struct Vec2f
{
    float x, y;

    Vec2f() : x{0}, y{0}
    {
    }

    Vec2f(float x, float y) : x{x}, y{y}
    {
    }

    friend Vec2f operator+(const Vec2f &lhs, const Vec2f &rhs);
    friend Vec2f operator+(const Vec2f &lhs, const float &rhs);

    void operator+=(Vec2f &&rhs)
    {
        x += rhs.x;
        y += rhs.y;
    }

    friend Vec2f operator-(const Vec2f &lhs, const Vec2f &rhs);
    friend Vec2f operator-(float lhs, const Vec2f &rhs);
    friend Vec2f operator-(const Vec2f &lhs, float rhs);

    friend Vec2f operator/(float lhs, const Vec2f &rhs);
    friend Vec2f operator/(const Vec2f &lhs, float rhs);

    friend Vec2f operator*(float lhs, const Vec2f &rhs);
    friend Vec2f operator*(const Vec2f &lhs, float rhs);
    friend Vec2f operator*(const Vec2f &lhs, const Vec2f &rhs);
};

struct Rect
{
    Vec2f pos;
    Vec2f size;
};

std::string read_file(const std::string &path);

std::string toAbsolute(const std::string &path, const std::string &parent = "../res");

std::vector<int> parse_coords(const std::string &coords);

std::vector<std::vector<int>> parse_level(const std::string &coords);

std::vector<SDL_Rect> parse_spritesheet(const std::string &coords);

SDL_Texture *loadImage(const std::string &path, SDL_Renderer *renderer);

} // namespace smb
