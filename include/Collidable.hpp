#pragma once

namespace smb
{

class Collidable
{
  public:
    virtual ~Collidable() = default;
    virtual void update(float dt) = 0;
};

} // namespace smb