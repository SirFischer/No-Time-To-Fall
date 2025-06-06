#pragma once

#include "System.hpp"

class World;
struct TransformComponent;
struct InputComponent;

class InputSystem : public System {
private:
	World* mWorld;

public:
	InputSystem(World* world);
	void Update(float deltaTime) override;
	void HandleEvent(const sf::Event& event) override;
	bool ShouldProcessEntity(EntityID entity) override;
};