#include "Player.hpp"
#include "Util.hpp"
#include <SDL_image.h>
#include <chrono>
#include <iostream>

namespace smb
{

Player::Player(Vec2<float> position, SDL_Rect boundingBox) : m_position{position}, m_boundingBox{boundingBox}
{
    const auto coords_f = read_file("textCoords.txt");
    auto coords = parse_spritesheet(coords_f);
    m_frames = std::move(coords);
    m_boundingBox = m_frames[14];
    m_boundingBox.x = 200;
    m_boundingBox.y = 804;
    m_boundingBox.w *= 2;
    m_boundingBox.h *= 2;
    m_acceleration = Vec2<float>{0, 0.0026f};
    m_velocity = Vec2<float>{0, 0};
}

Player::~Player()
{
    SDL_DestroyTexture(m_texture);
    m_texture = NULL;
}

void Player::update(float dt)
{
    
}

void Player::render(float dt, SDL_Renderer *renderer)
{
    if (m_texture == NULL)
    {
        loadImage(toAbsolute("characters.gif"), renderer, &m_texture);
    }

    SDL_RenderCopy(renderer, m_texture, &m_frames[14], &m_boundingBox);
}

} // namespace smb
