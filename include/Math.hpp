#pragma once

#include <ostream>
#include <random>
#include <utility>

namespace smb::math
{

struct Vec2f
{
    float x, y;

    constexpr Vec2f() : x{0}, y{0}
    {
    }

    constexpr Vec2f(float x, float y) : x{x}, y{y}
    {
    }

    constexpr friend Vec2f operator+(const Vec2f &lhs, const Vec2f &rhs);
    constexpr friend Vec2f operator+(const Vec2f &lhs, const float &rhs);
    constexpr friend Vec2f operator+(const float &lhs, const Vec2f &rhs);

    constexpr friend Vec2f operator-(const Vec2f &lhs, const Vec2f &rhs);
    constexpr friend Vec2f operator-(float lhs, const Vec2f &rhs);
    constexpr friend Vec2f operator-(const Vec2f &lhs, float rhs);

    constexpr friend Vec2f operator/(float lhs, const Vec2f &rhs);
    constexpr friend Vec2f operator/(const Vec2f &lhs, float rhs);

    constexpr friend Vec2f operator*(float lhs, const Vec2f &rhs);
    constexpr friend Vec2f operator*(const Vec2f &lhs, float rhs);
    constexpr friend Vec2f operator*(const Vec2f &lhs, const Vec2f &rhs);
};

struct Rect
{
    Vec2f pos;
    Vec2f size;

    friend std::ostream &operator<<(const std::ostream &os, const Rect &rect);
};

inline std::ostream &operator<<(std::ostream &os, const Rect &rect)
{
    return os << "[Rect] position x: " << rect.pos.x << "  position y: " << rect.pos.y << "  size x: " << rect.size.x
              << "  size y: " << rect.size.y;
}

constexpr Vec2f operator/(float lhs, const Vec2f &rhs)
{
    return {lhs / rhs.x, lhs / rhs.y};
}

constexpr Vec2f operator/(const Vec2f &lhs, float rhs)
{
    return {lhs.x / rhs, lhs.y / rhs};
}

constexpr Vec2f operator-(float lhs, const Vec2f &rhs)
{
    return {lhs - rhs.x, lhs - rhs.y};
}

constexpr Vec2f operator-(const Vec2f &lhs, float rhs)
{
    return {lhs.x - rhs, lhs.y - rhs};
}

constexpr Vec2f operator-(const Vec2f &lhs, const Vec2f &rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

constexpr Vec2f operator+(const float &lhs, const Vec2f &rhs)
{
    return {lhs + rhs.x, lhs + rhs.y};
}

constexpr Vec2f operator+(const Vec2f &lhs, const Vec2f &rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

constexpr Vec2f operator*(float lhs, const Vec2f &rhs)
{
    return {lhs * rhs.x, lhs * rhs.y};
}

constexpr Vec2f operator*(const Vec2f &lhs, float rhs)
{
    return {lhs.x * rhs, lhs.y * rhs};
}

constexpr Vec2f operator+(const Vec2f &lhs, const float &rhs)
{
    return {lhs.x + rhs, lhs.y + rhs};
}

template <typename IntegralType> IntegralType generateRandomInt(const IntegralType lower, const IntegralType upper)
{
    std::random_device device;
    std::mt19937 mt(device());
    std::uniform_int_distribution<IntegralType> distribution(lower, upper);
    return distribution(mt);
}

} // namespace smb::math
