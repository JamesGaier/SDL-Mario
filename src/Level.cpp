#include "Level.hpp"
#include <iostream>
#include "StaticTileGraphicsComponent.hpp"
#include "NullPhysicsComponent.hpp"
#include "NullInputComponent.hpp"
#include "PlayerGraphicsComponent.hpp"
#include "PlayerPhysicsComponent.hpp"
#include "PlayerInputComponent.hpp"

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
                    std::make_unique<StaticTileGraphicsComponent>(TileColor::BROWN, Vec2<float>{x * BLOCK_SIZE, y * BLOCK_SIZE}),
                    std::make_unique<NullPhysicsComponent>(),
                    std::make_unique<NullInputComponent>()
                ));
                ++idx;
                break;
            }
            case TileType::PLAYER: {
                
                auto player = std::make_unique<GameObject>(
                    std::make_unique<PlayerGraphicsComponent>(),
                    std::make_unique<PlayerPhysicsComponent>(),
                    std::make_unique<PlayerInputComponent>()
                );
                
                player->m_acceleration = Vec2<float>{0, 0.0026f};
                player->m_velocity = Vec2<float>{0, 0};
                player->m_position = Vec2<float>{x * BLOCK_SIZE, y * BLOCK_SIZE};
                
                m_level.push_back(std::move(player));
                
                ++idx;
                break;
            }
            }
        }
    }
}

void Level::render(float dt, SDL_Renderer *renderer)
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