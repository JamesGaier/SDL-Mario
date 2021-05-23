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
    Player(Vec2<float> position, SDL_Rect boundingBox);
    ~Player() override;
    void update(float dt) override;
    void render(float dt, SDL_Renderer *renderer) override;

  private:
    const std::string MARIO_PLACEHOLDER{"/home/james/Documents/SDL-Mario/res/characters.gif"};
    unsigned m_coins{};
    unsigned m_points{};
    unsigned m_lives;
    bool m_isJumping{false};
    bool m_alive{true};
    Vec2<float> m_position;
    SDL_Rect m_boundingBox;
    Vec2<float> m_velocity;
    std::vector<SDL_Rect> m_frames; 
    SDL_Texture *m_texture{NULL};

    void loadImage(const std::string &path, SDL_Renderer *renderer);
};
} // namespace smb