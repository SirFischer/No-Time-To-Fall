#pragma once 

#include "Component.hpp"

struct JumpForceComponent : public Component
{
	JumpForceComponent() = default;

	float jumpForce = 250.0f;
	bool isJumping = false;
	float extraJumpForce = 800.0f;
	float maxJumpTime = 0.3f;
	float jumpTimer = 0.0f;
};