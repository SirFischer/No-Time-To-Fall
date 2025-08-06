#pragma once 

#include "Component.hpp"

struct MovementSpeedComponent : public Component
{
	MovementSpeedComponent() = default;

	bool enabled = true;

	float acceleration = 1000.0f;
	float airbornAcceleration = 400.0f;
	float maxSpeed = 250.0f;
	float airFriction = 0.93f;
	float groundFriction = 0.83f;
};