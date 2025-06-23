#pragma once 

#include "Component.hpp"

struct InputComponent : public Component
{
	InputComponent() = default;

	bool isMovingRight = false;
	bool isMovingLeft = false;
	bool isJumping = false;
	bool isCrouching = false;
};