#include "Animator.hpp"
#include "Util.hpp"
#include <iostream>

namespace smb
{

Animator::~Animator()
{
    SDL_DestroyTexture(m_spritesheet);
}

Animator::Animator(const Animator &animator) 
  :  m_renderer{animator.getRenderer()}, m_spritesheet{animator.getSpriteSheet()}, m_frames{animator.getFrames()}
{
}

Animator::Animator(SDL_Renderer *renderer, const std::string &spriteFileName, const std::string &coordsFileName)
    : m_renderer{renderer}
{
    try
    {
        const auto coordsFile = read_file(coordsFileName);
        auto coords = parse_spritesheet(coordsFile);
        m_frames = std::move(coords);
        m_spritesheet = loadImage(toAbsolute(spriteFileName), m_renderer);
    }
    catch (std::exception &ex)
    {
        std::cout << "An exception occured" << ex.what() << std::endl;
        exit(0);
    }
}

void Animator::addAnimation(const std::string &name, unsigned begin, unsigned end)
{
    m_animations.emplace(name, std::make_pair(begin, end));
}

void Animator::setAnimation(const std::string &name)
{
    if (m_animations.count(name) != 0 && m_currentAnimation != name)
    {
        m_currentAnimation = name;
        auto currentAnimation = m_animations.at(m_currentAnimation);
        m_currentFrame = currentAnimation.first * speed;
    }
}

void Animator::renderAnimation(math::Rect &scaleRect)
{
    if (m_animations.count(m_currentAnimation) != 0)
    {
        auto currentAnimation = m_animations.at(m_currentAnimation);
        int begin = currentAnimation.first * speed;
        int end = currentAnimation.second * speed;

        m_imageRenderer.render(m_renderer, m_spritesheet, m_frames.at(m_currentFrame / speed), scaleRect);

        if (m_currentFrame >= end)
        {
            m_currentFrame = begin;
        }
        else
        {
            ++m_currentFrame;
        }
    }
}

} // namespace smb
