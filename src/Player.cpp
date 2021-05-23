#include "Player.hpp"
#include <SDL_image.h>
#include <chrono>
#include "Util.hpp"

namespace smb
{

Player::Player(Vec2<float> position, SDL_Rect boundingBox) : m_position{position}, m_boundingBox{boundingBox}
{
    SDL_Rect f1 = SDL_Rect{1, 4, 16, 29};
    SDL_Rect f2 = SDL_Rect{20, 4, 16, 29};
    SDL_Rect f3 = SDL_Rect{39, 3, 14, 30};
    SDL_Rect f4 = SDL_Rect{56, 4, 16, 29};
    SDL_Rect f5 = SDL_Rect{75, 3, 16, 30};
    SDL_Rect f6 = SDL_Rect{94, 6, 14, 27};
    SDL_Rect f7 = SDL_Rect{111, 3, 14, 30};
    SDL_Rect f8 = SDL_Rect{128, 2, 16, 31};
    SDL_Rect f9 = SDL_Rect{147, 1, 16, 32};
    SDL_Rect f10 = SDL_Rect{166, 1, 16, 32};
    SDL_Rect f11 = SDL_Rect{184, 2, 14, 31};
    SDL_Rect f12 = SDL_Rect{201, 3, 16, 30};
    SDL_Rect f13 = SDL_Rect{220, 11, 16, 32};
    SDL_Rect f14 = SDL_Rect{239, 1, 16, 22};
    SDL_Rect f15 = SDL_Rect{239, 1, 16, 32};
    SDL_Rect f16 = SDL_Rect{258, 1, 16, 32};
    SDL_Rect f17 = SDL_Rect{277, 11, 16, 22};
    SDL_Rect f18 = SDL_Rect{296, 3, 16, 30};

    m_frames.push_back(f1);
    m_frames.push_back(f2);
    m_frames.push_back(f3);
    m_frames.push_back(f4);
    m_frames.push_back(f5);
    m_frames.push_back(f6);
    m_frames.push_back(f7);
    m_frames.push_back(f8);
    m_frames.push_back(f9);
    m_frames.push_back(f10);
    m_frames.push_back(f11);
    m_frames.push_back(f12);
    m_frames.push_back(f13);
    m_frames.push_back(f14);
    m_frames.push_back(f15);
    m_frames.push_back(f16);
    m_frames.push_back(f17);
    m_frames.push_back(f18);
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

    //SDL_RenderCopy(renderer, m_texture, NULL, &m_boundingBox);

    for(const auto &frame : m_frames)
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
