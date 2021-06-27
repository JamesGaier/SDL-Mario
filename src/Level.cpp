#include "Level.hpp"
#include "NullInputComponent.hpp"
#include "NullPhysicsComponent.hpp"
#include "PlayerGraphicsComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "PlayerPhysicsComponent.hpp"
#include "StaticTileGraphicsComponent.hpp"
#include <iostream>

namespace smb
{

std::unique_ptr<GameObject> Level::makeGround(int x, int y, int idx)
{
    return std::make_unique<GameObject>(std::make_unique<StaticTileGraphicsComponent>(TileColor::BROWN, Vec2f{x, y}),
                                        std::make_unique<NullPhysicsComponent>(),
                                        std::make_unique<NullInputComponent>(), idx,
                                        Rect{Vec2f{x, y}, Vec2f{BLOCK_SIZE, BLOCK_SIZE}});
}

std::unique_ptr<GameObject> Level::makePlayer(int x, int y, int idx)
{
    return std::make_unique<GameObject>(
        std::make_unique<PlayerGraphicsComponent>(), std::make_unique<PlayerPhysicsComponent>(m_level),
        std::make_unique<PlayerInputComponent>(), idx, Rect{Vec2f{x, y}, Vec2f{MARIO_WIDTH, MARIO_HEIGHT}});
}

Level::Level(const std::string &path)
{
    auto levelStr = read_file(path);
    auto levelData = parse_level(levelStr);

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
                m_level.push_back(makeGround(x * BLOCK_SIZE, y * BLOCK_SIZE, idx));
                ++idx;
                break;
            }
            case TileType::PLAYER: {
                auto player = makePlayer(x * BLOCK_SIZE, y * BLOCK_SIZE, idx);

                player->acceleration = Vec2f{0, 80}; // magic number please make name value please
                player->velocity = Vec2f{0, 0};

                m_level.push_back(std::move(player));

                ++idx;
                break;
            }
            }
        }
    }
}

void Level::render(SDL_Renderer *renderer)
{
    for (const auto &el : m_level)
    {
        el->render(renderer);
    }
}

void Level::update(float dt)
{
    for (const auto &el : m_level)
    {
        el->update(dt);
    }
}

} // namespace smb