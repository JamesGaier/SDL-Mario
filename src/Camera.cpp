#include "Camera.hpp"
#include "GameObject.hpp"

namespace smb
{

Camera::Camera(SDL_Renderer *renderer, int width, int height) : m_renderer{renderer}, m_levelWidth{width}, m_levelHeight{height}
{
    m_cameraX = 0;
}

void Camera::scroll(math::Rect renderBox)
{
    renderBox.pos.x -= m_cameraX;
}

void Camera::update(const GameObject &gameObject)
{
    m_cameraX = (gameObject.getPositionX() + gameObject.getBoundingBoxSizeX() / 2) - m_screenWidth / 2;

    if(m_cameraX < 0)
    {
        m_cameraX = 0;
    }
    if(m_cameraX > m_levelWidth - m_screenWidth)
    {
        m_cameraX = m_levelWidth - m_screenWidth;
    }
}

float &Camera::getPositionX()
{
    return m_cameraX;
}

} // namespace smb
