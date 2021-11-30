#pragma once

#include "GraphicsComponent.hpp"
#include <SDL.h>

namespace smb
{

// strategy for Graphics component that accounts for object with no graphical effects in the game
class NullGraphicsComponent final : public GraphicsComponent
{
    ~NullGraphicsComponent() override = default;

    void render(GameObject &, SDL_Renderer *) override
    {
    }
};

} // namespace smb