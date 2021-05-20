#pragma once
#include "Collidable.hpp"
#include "Renderable.hpp"
#include <SDL_image.h>

namespace smb
{
    class Player : public Collidable, public Renderable
    {
    public:
        void update(float dt) override;
        void render(float dt) override;
    };
}