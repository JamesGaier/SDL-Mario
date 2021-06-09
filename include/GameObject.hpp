#pragma once
#include "Util.hpp"

namespace smb
{

class GameObject
{
public:
    Vec2<float> m_position;
    Vec2<float> m_velocity;
    Vec2<float> m_acceleration;
};

} // namespace smb