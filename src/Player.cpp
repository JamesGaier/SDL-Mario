#include "Player.hpp"
#include "Util.hpp"
#include <SDL_image.h>
#include <chrono>
#include <iostream>

namespace smb
{

Player::Player(Vec2<float> position) : m_position{position}
{
    const auto coords_f = read_file("textCoords.txt");
    auto coords = parse_spritesheet(coords_f);
    m_frames = std::move(coords);
    m_boundingBox.w = m_width;
    m_boundingBox.h = m_height;
    m_boundingBox.x = position.x;
    m_boundingBox.y = position.y - m_heightOffset;
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
    m_velocity.x += m_acceleration.x * dt;
    m_velocity.y += m_acceleration.y * dt;
    m_position.x += m_velocity.x * dt + m_acceleration.x * dt * dt;
    m_position.y += m_velocity.y * dt + m_acceleration.y * dt * dt;
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
