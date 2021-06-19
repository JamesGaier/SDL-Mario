#pragma once
#include "Command.hpp"
#include "Ground.hpp"
#include "Player.hpp"
#include "Renderable.hpp"
#include "Util.hpp"
#include <memory>
#include <vector>

namespace smb
{


class Level
{
  public:
    Level(const std::string &path);
    Command *getACommand() const;
    Command *getDCommand() const;
    void render(float dt, SDL_Renderer *renderer);
    void update(float dt);
  private:
    std::vector<std::unique_ptr<GameObject>> m_level;
};

} // namespace smb