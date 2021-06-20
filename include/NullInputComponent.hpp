#pragma once
#include "InputComponent.hpp"

namespace smb
{

class NullInputComponent final : public InputComponent
{
  public:
    ~NullInputComponent() override = default;
    void update(GameObject &GameObject) override
    {
    }
};

} // namespace smb