#pragma once
#include "GameObject.hpp"

namespace smb
{

class GameObject;
class InputComponent
{
  public:
    virtual ~InputComponent() = default;
    virtual void update(GameObject &gameObject) = 0;
};

} // namespace smb