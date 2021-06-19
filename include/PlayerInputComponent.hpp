#include "InputComponent.hpp"
#include "Command.hpp"
#include <SDL.h>
#include <memory>

namespace smb
{

class PlayerInputComponent : public InputComponent
{
public:
	~PlayerInputComponent() = default;
	void update(GameObject &gameObject);
private:
	Command *handleKeyInput();
	std::unique_ptr<Command> m_aCommand;
	std::unique_ptr<Command> m_dCommand;
};

}