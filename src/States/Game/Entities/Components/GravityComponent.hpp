#pragma once

#include "Component.hpp"

struct GravityComponent : public Component {
	float gravity = 1200.f;
	float fallingMultiplier = 1.5f;
	float terminalVelocity = 2000.0f;

	GravityComponent() = default;
	GravityComponent(float gravity, float terminalVelocity)
		: gravity(gravity), terminalVelocity(terminalVelocity) {}
};