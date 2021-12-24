#include "Level.hpp"
#include "NullInputComponent.hpp"
#include "NullPhysicsComponent.hpp"
#include "PlayerGraphicsComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "PlayerPhysicsComponent.hpp"
#include "ResourceFactory.hpp"
#include "StaticTileGraphicsComponent.hpp"
#include <iostream>

namespace smb
{

std::unique_ptr<GameObject> Level::makeGround(float x, float y)
{
    auto scaleRect = math::Rect{math::Vec2f{x, y}, math::Vec2f{BLOCK_SIZE, BLOCK_SIZE}};
    auto ground = std::make_unique<GameObject>(
        std::make_unique<StaticTileGraphicsComponent>(TileColor::BROWN, math::Vec2f{x, y}, m_renderer, m_camera.getPositionX()),
        std::make_unique<NullPhysicsComponent>(), std::make_unique<NullInputComponent>(), scaleRect);

    ground->ID = 2;

    return ground;
}

std::unique_ptr<GameObject> Level::makePlayer(float x, float y)
{
    auto scaleRect = math::Rect{math::Vec2f{x, y}, math::Vec2f{MARIO_WIDTH, MARIO_HEIGHT}};
    auto playerPhysicsComponent = std::make_unique<PlayerPhysicsComponent>(m_level, m_camera);
    auto playerGraphicsComponent = std::make_unique<PlayerGraphicsComponent>(m_renderer, m_camera.getPositionX());
    auto player = std::make_unique<GameObject>(
        std::move(playerGraphicsComponent), std::move(playerPhysicsComponent),
        std::make_unique<PlayerInputComponent>(playerPhysicsComponent.get(), playerGraphicsComponent.get(), m_renderer),
        scaleRect);

    constexpr static auto startOffset = 4;
    auto boundingBox = player->getBoundingBox();
    boundingBox.size.x -= startOffset;
    player->setBoundingBox(boundingBox);

    constexpr static auto gravity = 800.0f;
    constexpr static auto initialVerticalVelocity = 300.0f;
    player->setAccelerationY(gravity);
    player->setVelocityY(initialVerticalVelocity);

    player->ID = 1;

    return player;
}

Level::Level(const std::string &path, SDL_Renderer *renderer) : m_renderer{renderer}, m_camera(m_renderer, m_levelWidth, m_levelHeight)
{
    auto levelStr = read_file(path);
    auto levelData = parse_level(levelStr);

    ResourceFactory::loadResource("textCoordsStatic.txt", "tiles.png", "static_assets", m_renderer);
    ResourceFactory::loadResource("textCoords.txt", "characters.gif", "player", m_renderer);

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
                auto ground = makeGround(x * BLOCK_SIZE, y * BLOCK_SIZE);
                m_level.push_back(std::move(ground));
                ++idx;
                break;
            }
            case TileType::SPAWN: {
                auto player = makePlayer(x * BLOCK_SIZE, y * BLOCK_SIZE);
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

void Level::render()
{
    for (const auto &el : m_level)
    {
        el->render();
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
