#pragma once

#include "Component.hpp"
#include <SFML/Graphics/Rect.hpp>

struct ColliderComponent : public Component {
	sf::FloatRect boundingBox;
	bool isTrigger = false;

	ColliderComponent() = default;
	ColliderComponent(float x, float y, float width, float height)
		: boundingBox(x, y, width, height) {}
	ColliderComponent(const sf::FloatRect& rect)
		: boundingBox(rect) {}
};