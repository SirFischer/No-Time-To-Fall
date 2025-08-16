#pragma once

#include "Component.hpp"
#include <SFML/System/Time.hpp>

struct BlockPlacementComponent : public Component {
	sf::Time currentCooldown = sf::seconds(0.0f);

	sf::Time ghostPlacementCooldown = sf::seconds(3.0f);
	sf::Time placementCooldown = sf::seconds(1.5f);

	BlockPlacementComponent() = default;
};