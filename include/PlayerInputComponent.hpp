#include "InputComponent.hpp"
#include <SDL.h>
#include <memory>

namespace smb
{

class PlayerInputComponent : public InputComponent
{
  public:
    ~PlayerInputComponent() = default;
    void update(GameObject &gameObject);
};

} // namespace smb