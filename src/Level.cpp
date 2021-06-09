#include "Level.hpp"
#include <iostream>

namespace smb
{

Level::Level(const std::string &path)
{
    auto levelStr = read_file(path);
    auto levelData = parse_level(levelStr);

    const auto BLOCK_SIZE = 32;
    const auto HEIGHT = 900;
    auto idx = 0;
    for (auto y = 0u; y < levelData.size(); ++y)
    {
        for (auto x = 0u; x < levelData[y].size(); ++x)
        {
            auto type = static_cast<TileType>(levelData[y][x]);
            switch (type)
            {
            case TileType::GROUND: {
                m_level.push_back(
                    std::make_unique<Ground>(GroundType::BROWN, Vec2<float>{x * BLOCK_SIZE, y * BLOCK_SIZE}));
                ++idx;
                break;
            }
            case TileType::PLAYER: {
                m_level.push_back(std::make_unique<Player>(Vec2<float>(x * BLOCK_SIZE, y * BLOCK_SIZE)));
                auto player = dynamic_cast<Player *>(m_level[idx].get());
                m_aCommand.reset(new ACommand(player));
                m_dCommand.reset(new DCommand(player));
                ++idx;
                break;
            }
            }
        }
    }
}

Command *Level::getACommand() const
{
    return m_aCommand.get();
}

Command *Level::getDCommand() const
{
    return m_dCommand.get();
}

void Level::render(float dt, SDL_Renderer *renderer)
{
    for (const auto &el : m_level)
    {
        el->render(0, renderer);
    }
}

void Level::update(float dt)
{
    for (const auto &el : m_level)
    {
        auto col_el = dynamic_cast<Collidable *>(el.get());
        if (!col_el)
        {
            col_el->update(dt);
        }
    }
}

} // namespace smb