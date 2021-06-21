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
                m_level.push_back(std::make_unique<GameObject>(
                    std::make_unique<StaticTileGraphicsComponent>(TileColor::BROWN,
                                                                  Vec2<float>{x * BLOCK_SIZE, y * BLOCK_SIZE}),
                    std::make_unique<NullPhysicsComponent>(),
                    std::make_unique<NullInputComponent>(), 
                    idx,
                    SDL_Rect{static_cast<int>(x) * BLOCK_SIZE, static_cast<int>(y) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE}));
                ++idx;
                break;
            }
            case TileType::PLAYER: {
                constexpr int MARIO_WIDTH = 32;
                constexpr int MARIO_HEIGHT = 64;
                auto player = std::make_unique<GameObject>(std::make_unique<PlayerGraphicsComponent>(),
                                                           std::make_unique<PlayerPhysicsComponent>(m_level),
                                                           std::make_unique<PlayerInputComponent>(),
                                                           idx,
                                                           SDL_Rect{static_cast<int>(x) * BLOCK_SIZE, static_cast<int>(y) * BLOCK_SIZE, MARIO_WIDTH, MARIO_HEIGHT});

                player->m_acceleration = Vec2<float>{0, 80}; // magic number please make name value please
                player->m_velocity = Vec2<float>{0, 0};

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