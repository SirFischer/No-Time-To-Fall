#pragma once 

#include "Component.hpp"

struct InputComponent : public Component
{
	InputComponent(bool enabled) : enabled(enabled) {}

	bool enabled = true;

	bool isMovingRight = false;
	bool isMovingLeft = false;
	bool isJumping = false;
	bool isCrouching = false;
};