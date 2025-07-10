#pragma once
#include "Component.hpp"

struct RespawnComponent : public Component {
	bool respawn = false;
	sf::Vector2f lastSafePosition = {0.0f, 0.0f};

	bool isRespawning = false;
	float respawnTime = 1.0f;
	float respawnClock = 0.0f;

    RespawnComponent() = default;
};
