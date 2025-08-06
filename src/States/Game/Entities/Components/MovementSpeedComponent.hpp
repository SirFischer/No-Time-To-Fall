#pragma once 

#include "Component.hpp"

struct MovementSpeedComponent : public Component
{
	MovementSpeedComponent() = default;

	bool enabled = true;

	float acceleration = 800.0f;
	float airbornAcceleration = 200.0f;
	float maxSpeed = 400.0f;
	float airFriction = 0.93f;
	float groundFriction = 0.83f;
};