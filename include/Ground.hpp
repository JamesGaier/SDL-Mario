#pragma once
#include "Collidable.hpp"
#include "Renderable.hpp"
#include "Util.hpp"
#include <SDL.h>
#include <string>
#include <vector>

namespace smb
{
enum class GroundType
{
    BROWN,
    BLUE,
    WHITE,
    GREEN
};
class Ground : public Renderable
{
  public:
    ~Ground() override = default;
    Ground(GroundType &&type, const Vec2<float> &pos);
    void render(float dt, SDL_Renderer *renderer) override;


  private:
    SDL_Texture *m_texture{NULL};
    SDL_Rect m_spriteSheetPos;
    SDL_Rect m_boundingBox;
    GroundType m_type;
    Vec2<float> m_pos;

    void initGround(const std::vector<SDL_Rect> &tiles);
};
} // namespace smb