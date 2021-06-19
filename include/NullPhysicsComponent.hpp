#pragma once

#include "PhysicsComponent.hpp"

namespace smb
{

class NullPhysicsComponent: public PhysicsComponent
{
public:
	~NullPhysicsComponent() override = default;
	void update(GameObject &gameObject, float dt) override;
};

}