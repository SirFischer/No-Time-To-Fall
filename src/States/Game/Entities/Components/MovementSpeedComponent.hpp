#pragma once 

#include "Component.hpp"

struct MovementSpeedComponent : public Component
{
	MovementSpeedComponent() = default;

	bool enabled = true;

	float acceleration = 1500.0f;
	float airbornAcceleration = 500.0f;
	float maxSpeed = 500.0f;
	float airFriction = 0.95f;
	float groundFriction = 0.85f;
};