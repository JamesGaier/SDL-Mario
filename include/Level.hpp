#pragma once

#include "GameObject.hpp"
#include "SDL_render.h"
#include "Util.hpp"
#include <memory>
#include <vector>

namespace smb
{

class Level
{
  public:
    using World = std::vector<std::unique_ptr<GameObject>>;
    Level(const std::string &path, SDL_Renderer *renderer);
    void render();
    void update(float dt);

  private:
    constexpr static auto BLOCK_SIZE = 32;
    constexpr static auto MARIO_WIDTH = 32;
    constexpr static auto MARIO_HEIGHT = 64;

    World m_level;
    SDL_Renderer *m_renderer;

    std::unique_ptr<GameObject> makeGround(float x, float y);

    std::unique_ptr<GameObject> makePlayer(float x, float y);
};

} // namespace smb
