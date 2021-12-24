#pragma once
#include "Math.hpp"
#include "SDL_render.h"
#include "ImageRenderer.hpp"
#include "GameObject.hpp"
#include <SDL.h>

namespace smb
{

class GameObject;
class Camera
{
public:
    ~Camera() = default;

    Camera(SDL_Renderer *renderer, int width, int height);

    void scroll(math::Rect renderBox);

    void update(const GameObject &go);

    float &getPositionX();
    
private:
    math::Rect m_cameraRect;
    SDL_Renderer *m_renderer;
    int m_levelWidth;
    int m_levelHeight;
    float m_cameraX;
    constexpr static int m_screenWidth = 1600;
    constexpr static int m_screenHeight = 960;
    ImageRenderer m_imageRenderer;
};

} // namespace smb
