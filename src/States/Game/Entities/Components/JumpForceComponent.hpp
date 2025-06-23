#pragma once 

#include "Component.hpp"

struct JumpForceComponent : public Component
{
	JumpForceComponent() = default;

	float jumpForce = 200.0f;
};