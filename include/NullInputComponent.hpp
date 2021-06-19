#pragma once
#include "InputComponent.hpp"

namespace smb
{

class NullInputComponent : public InputComponent
{
public:
	~NullInputComponent() override = default;
	void update(GameObject &GameObject) override; 
};

}