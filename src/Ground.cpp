#include "Ground.hpp"
#include "Util.hpp"
#include <iostream>
#include <utility>

namespace smb
{
Ground::Ground(GroundType &&type, const Vec2<float> &pos) : m_type{std::move(type)}, m_pos{pos}
{
    m_path = read_file("textCoordsStatic.txt");
    auto tiles = parse_coords(m_path);
    initGround(tiles);
}

void Ground::render(float dt, SDL_Renderer *renderer)
{
    if (m_texture == NULL)
    {
        loadImage(toAbsolute("tiles.png"), renderer, &m_texture);
    }

    SDL_RenderCopy(renderer, m_texture, &m_spriteSheetPos, &m_boundingBox);
}

void Ground::initGround(const std::vector<SDL_Rect>& tiles)
{
    switch(m_type)
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
    m_boundingBox = SDL_Rect{static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_spriteSheetPos.w * 2, m_spriteSheetPos.h * 2};
}
} // namespace smb