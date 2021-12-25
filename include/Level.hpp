#pragma once

#include "GameObject.hpp"
#include "SDL_render.h"
#include "Camera.hpp"
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
    constexpr static int m_levelWidth = 1696;
    constexpr static int m_levelHeight = 960;

    World m_level;
    SDL_Renderer *m_renderer;
    Camera m_camera;

    std::unique_ptr<GameObject> makeGround(float x, float y);

    std::unique_ptr<GameObject> makePlayer(float x, float y);
};

} // namespace smb
