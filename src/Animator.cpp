#include "Animator.hpp"
#include "File.hpp"
#include "ResourceFactory.hpp"
#include <iostream>

namespace smb
{

Animator::Animator(SDL_Renderer *renderer)
    : m_renderer{renderer}
{
    auto resource = ResourceFactory::getResource("player");
    auto coords = resource->coords;
    m_frames = std::move(coords);
    m_spritesheet = resource->texture;
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

void Animator::renderAnimation()
{
    if (m_animations.count(m_currentAnimation) != 0)
    {
        auto currentAnimation = m_animations.at(m_currentAnimation);
        int begin = currentAnimation.first * speed;
        int end = currentAnimation.second * speed;

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
