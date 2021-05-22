#pragma once
#include "Collidable.hpp"
#include "Renderable.hpp"
#include <SDL.h>
#include <SDL_image.h>

namespace smb
{
    class Player : public Collidable, public Renderable
    {
    public:
        Player(Vec2<float> position, SDL_Rect boundingBox);
        ~Player() override;
        void update(float dt) override;
        void render(float dt, SDL_Surface* screenSurface) override;
    private:
        const std::string MARIO_PLACEHOLDER{"/home/james/Documents/SDL-Mario/res/mario.png"};
        unsigned m_coins{};
        unsigned m_points{};
        unsigned m_lives;
        bool m_isJumping{false};
        bool m_alive{true};
        Vec2<float> m_position;
        SDL_Rect m_boundingBox;
        Vec2<float> m_velocity;
        SDL_Surface* playerSurface{NULL};

        void loadImage(const std::string& path, SDL_Surface* screenSurface);
    };
}