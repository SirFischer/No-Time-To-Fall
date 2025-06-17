#pragma once

#include "System.hpp"
#include "../../../../Events/Actions.hpp"

class World;
struct TransformComponent;
struct InputComponent;

class InputSystem : public System {
private:
	World* mWorld;
	Yuna::Core::EventHandler* mEventHandler;

public:
	InputSystem(World* world, Yuna::Core::EventHandler* eventHandler);
	void Update(float deltaTime) override;
	void HandleEvent(const sf::Event& event) override;
	bool ShouldProcessEntity(EntityID entity) override;
};