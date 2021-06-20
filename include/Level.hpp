#pragma once
#include "Ground.hpp"
#include "Renderable.hpp"
#include "GameObject.hpp"
#include "Util.hpp"
#include <memory>
#include <vector>

namespace smb
{

class Level
{
  public:
    Level(const std::string &path);
    void render(SDL_Renderer *renderer);
    void update(float dt);

  private:
    std::vector<std::unique_ptr<GameObject>> m_level;
};

} // namespace smb