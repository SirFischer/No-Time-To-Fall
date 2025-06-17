#pragma once

#include "Component.hpp"

struct GravityComponent : public Component {
	float gravity = 9.81f;
	float terminalVelocity = 53.0f;

	GravityComponent() = default;
	GravityComponent(float gravity, float terminalVelocity)
		: gravity(gravity), terminalVelocity(terminalVelocity) {}
};