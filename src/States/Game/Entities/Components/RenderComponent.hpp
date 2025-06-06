#pragma once

#include "Component.hpp"

struct RenderComponent : public Component
{
	std::shared_ptr<sf::Texture> texture = nullptr;
	sf::Sprite sprite;
	float width = 32.0f;
	float height = 32.0f;
	bool visible = true;

	RenderComponent() = default;
	RenderComponent(std::shared_ptr<sf::Texture> pTexture, float width, float height)
		: texture(pTexture), width(width), height(height)
	{
		sprite.setTexture(*texture);
	}
};
