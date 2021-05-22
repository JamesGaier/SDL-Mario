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
        void update(float dt) override;
        void render(float dt) override;
    private:
        unsigned m_coins{};
        unsigned m_points{};
        unsigned m_lives;
        bool m_isJumping{false};
        bool m_alive{true};
        Vec2<float> m_position;
        SDL_Rect m_boundingBox;
        Vec2<float> m_velocity;
    };
}