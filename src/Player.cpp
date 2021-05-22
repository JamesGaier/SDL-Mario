#include "Player.hpp"
#include <SDL_image.h>

namespace smb
{

Player::Player(Vec2<float> position, SDL_Rect boundingBox) : m_position{position}, m_boundingBox{boundingBox}
{
}

Player::~Player()
{
    SDL_FreeSurface(playerSurface);
}

void Player::update(float dt)
{
}

void Player::render(float dt, SDL_Surface *screenSurface)
{
    if (playerSurface == NULL)
    {
        loadImage(MARIO_PLACEHOLDER, screenSurface);
    }
    else
    {
        SDL_BlitSurface(playerSurface, NULL, screenSurface, NULL);
    }
}

void Player::loadImage(const std::string &path, SDL_Surface *screenSurface)
{
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "SDL_image Error: " << IMG_GetError();
    }
    else
    {
        playerSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
        if (playerSurface == NULL)
        {
            std::cout << "Unable to optimize image " << path.c_str() << "! SDL Error: " << SDL_GetError();
        }
    }
}
} // namespace smb
