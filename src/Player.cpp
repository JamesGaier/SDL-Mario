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
    auto coords = parse_coords(coords_f); 
    m_frames = std::move(coords);
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
        loadImage(MARIO_PLACEHOLDER, renderer);
    }

    // SDL_RenderCopy(renderer, m_texture, NULL, &m_boundingBox);

    for (const auto &frame : m_frames)
    {
        SDL_RenderCopy(renderer, m_texture, &frame, &frame);
    }

    SDL_RenderCopy(renderer, m_texture, &m_frames[4], &m_boundingBox);
}

void Player::loadImage(const std::string &path, SDL_Renderer *renderer)
{
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "SDL_image Error: " << IMG_GetError();
    }
    else
    {
        m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (m_texture == NULL)
        {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface(loadedSurface);
    }
}
} // namespace smb
