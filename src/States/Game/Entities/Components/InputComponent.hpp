#pragma once 

#include "Component.hpp"

struct InputComponent : public Component
{
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool action = false;

	InputComponent() = default;

	void Reset() {
		up = down = left = right = action = false;
	}
};