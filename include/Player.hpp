#pragma once
#include "Collidable.hpp"
#include "Renderable.hpp"
#include "Util.hpp"
#include <SDL.h>
#include <vector>

namespace smb
{
class Player : public Collidable, public Renderable
{
  public:
    Player(Vec2<float> position);
    ~Player() override;
    void update(float dt) override;
    void render(float dt, SDL_Renderer *renderer) override;

  private:
    const std::string MARIO_PLACEHOLDER;
    unsigned m_coins{};
    unsigned m_points{};
    const unsigned m_heightOffset{32};
    const unsigned m_width{32};
    const unsigned m_height{64};
    unsigned m_lives;
    bool m_isJumping{false};
    bool m_alive{true};
    Vec2<float> m_position;
    SDL_Rect m_boundingBox;
    Vec2<float> m_velocity;
    Vec2<float> m_acceleration;
    std::vector<SDL_Rect> m_frames;
    SDL_Texture *m_texture{NULL};
    
};
} // namespace smb