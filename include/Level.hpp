#pragma once

#include "GameObject.hpp"
#include "Util.hpp"
#include <memory>
#include <vector>

namespace smb
{

class Level
{
  public:
    using World = std::vector<std::unique_ptr<GameObject>>;
    Level(const std::string &path);
    void render(SDL_Renderer *renderer);
    void update(float dt);

  private:
    constexpr static auto BLOCK_SIZE = 32;
    constexpr static auto MARIO_WIDTH = 32;
    constexpr static auto MARIO_HEIGHT = 64;

    World m_level;

    std::unique_ptr<GameObject> makeGround(int x, int y, int idx);

    std::unique_ptr<GameObject> makePlayer(int x, int y, int idx);
};

} // namespace smb