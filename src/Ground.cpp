#include "Ground.hpp"
#include "Util.hpp"
#include <iostream>
#include <utility>

namespace smb
{
Ground::Ground(GroundType &&type, const Vec2<float> &pos) : m_type{std::move(type)}, m_pos{pos}
{
    // std::cout << m_pos.x << " " << m_pos.y << std::endl;
    auto tilesStr = read_file("textCoordsStatic.txt");
    auto tiles = parse_spritesheet(tilesStr);
    initGround(tiles);
}

void Ground::render(float dt, SDL_Renderer *renderer)
{
    if (m_texture == nullptr)
    {
        m_texture = loadImage(toAbsolute("tiles.png"), renderer);
    }

    SDL_RenderCopy(renderer, m_texture, &m_spriteSheetPos, &m_boundingBox);
}

void Ground::initGround(const std::vector<SDL_Rect> &tiles)
{
    switch (m_type)
    {
    case GroundType::BROWN: {
        m_spriteSheetPos = tiles[static_cast<unsigned>(GroundType::BROWN)];
        break;
    }
    case GroundType::BLUE: {
        m_spriteSheetPos = tiles[static_cast<unsigned>(GroundType::BLUE)];
        break;
    }
    case GroundType::WHITE: {
        m_spriteSheetPos = tiles[static_cast<unsigned>(GroundType::WHITE)];
        break;
    }
    case GroundType::GREEN: {
        m_spriteSheetPos = tiles[static_cast<unsigned>(GroundType::GREEN)];
        break;
    }
    default:
        std::cout << "error ground type invalid" << std::endl;
    }
    m_boundingBox = tiles[static_cast<unsigned>(m_type)];
    m_boundingBox.x = m_pos.x;
    m_boundingBox.y = m_pos.y;
    m_boundingBox.w *= 2;
    m_boundingBox.h *= 2;
}
} // namespace smb