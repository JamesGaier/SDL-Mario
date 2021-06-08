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

enum class TileType
{
    GROUND = 1,
    PLAYER,
    BREAKABLE,
    UP_PIPE,
    LEFT_PIPE,
    RIGHT_PIPE,
    DOWN_PIPE,
    MUSHROOM,
    QUESTION,
    INVISIBLE,
    SOLID,
    FLAG_POLE,
    CASTLE
};

class Level : public Renderable, public Collidable
{
  public:
    Level(const std::string &path);
    Command *getACommand() const;
    Command *getDCommand() const;
    void render(float dt, SDL_Renderer *renderer) override;
    void update(float dt) override;

  private:
    std::vector<std::unique_ptr<Renderable>> m_level;
    std::unique_ptr<Command> m_aCommand;
    std::unique_ptr<Command> m_dCommand;
};

} // namespace smb