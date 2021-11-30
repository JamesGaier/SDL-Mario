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

std::unique_ptr<GameObject> Level::makeGround(float x, float y, int idx)
{
    auto ground =
        std::make_unique<GameObject>(std::make_unique<StaticTileGraphicsComponent>(TileColor::BROWN, math::Vec2f{x, y}),
                                     std::make_unique<NullPhysicsComponent>(), std::make_unique<NullInputComponent>(),
                                     idx, math::Rect{math::Vec2f{x, y}, math::Vec2f{BLOCK_SIZE, BLOCK_SIZE}});

    ground->boundingBox = math::Rect{math::Vec2f{x, y}, math::Vec2f{x * BLOCK_SIZE, y * BLOCK_SIZE}};

    return ground;
}

std::unique_ptr<GameObject> Level::makePlayer(float x, float y, int idx)
{
    auto player = std::make_unique<GameObject>(
        std::make_unique<PlayerGraphicsComponent>(), std::make_unique<PlayerPhysicsComponent>(m_level),
        std::make_unique<PlayerInputComponent>(), idx, math::Rect{math::Vec2f{x, y}, math::Vec2f{MARIO_WIDTH, MARIO_HEIGHT}});

    constexpr static auto START_OFFSET = 4;
    player->boundingBox.size.x -= START_OFFSET;

    constexpr static auto GRAVITY = 800.0f;
    constexpr static auto INITIAL_VERTICAL_VELOCITY = 300.0f;
    player->accel = math::Vec2f{0, GRAVITY};
    player->vel = math::Vec2f{0, INITIAL_VERTICAL_VELOCITY};

    return player;
}

Level::Level(const std::string &path)
{
    auto levelStr = read_file(path);
    auto levelData = parse_level(levelStr);

    auto idx = 0;
    for (float y = 0u; y < levelData.size(); ++y)
    {
        for (float x = 0u; x < levelData[y].size(); ++x)
        {
            auto type = static_cast<TileType>(levelData[y][x]);
            switch (type)
            {
            case TileType::AIR:
                break;
            case TileType::GROUND: {
                auto ground = makeGround(x * BLOCK_SIZE, y * BLOCK_SIZE, idx);
                m_level.push_back(std::move(ground));
                ++idx;
                break;
            }
            case TileType::SPAWN: {
                auto player = makePlayer(x * BLOCK_SIZE, y * BLOCK_SIZE, idx);
                m_level.push_back(std::move(player));
                ++idx;
                break;
            }
            default: {
                std::cout << static_cast<int>(type) << " Is not currently supported." << std::endl;
                exit(1);
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