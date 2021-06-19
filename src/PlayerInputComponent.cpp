#include "PlayerInputComponent.hpp"

namespace smb
{
	
void PlayerInputComponent::update(GameObject &gameObject)
{
    if (auto *command = handleKeyInput(); command != nullptr)
    {
        command->execute(gameObject);
    }
}	


Command *PlayerInputComponent::handleKeyInput()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    if(currentKeyStates[SDL_SCANCODE_D])
    {
        return m_dCommand.get();
    }

    if(currentKeyStates[SDL_SCANCODE_A])
    {
        return m_aCommand.get();
    }
    
    return nullptr;
}

	
}