#pragma once
#include "InputComponent.hpp"

namespace smb
{

class NullInputComponent final : public InputComponent
{
  public:
    ~NullInputComponent() override = default;
    void update(GameObject &) override
    {
    }
};

} // namespace smb