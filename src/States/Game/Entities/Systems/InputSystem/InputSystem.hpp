#pragma once

#include "../System.hpp"
#include "../../../../../Events/Actions.hpp"

class World;
struct TransformComponent;
struct InputComponent;

class InputSystem : public System {
private:
	World* mWorld;
	Yuna::Core::EventHandler* mEventHandler;
	Yuna::Core::Window* mWindow;

public:
	InputSystem(World* world, Yuna::Core::EventHandler* eventHandler, Yuna::Core::Window* window);
	void Update(float deltaTime) override;
	void HandleEvent(const sf::Event& event) override;
	bool ShouldProcessEntity(EntityID entity) override;
};