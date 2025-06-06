#include "World.hpp"

void World::Init() {
	//test entity
	EntityID testEntity = CreateEntity();
	AddComponent<TransformComponent>(testEntity, 100.0f, 100.0f);
	AddComponent<RenderComponent>(testEntity, mResourceManager.LoadTexture("assets/textures/Dog.png"), 50, 50);
	AddComponent<VelocityComponent>(testEntity, 50.0f, 0.0f);
	AddComponent<InputComponent>(testEntity);

}

void World::HandleEvent(const sf::Event& event) {
	for (const auto& system : mSystems) {
		system->HandleEvent(event);
	}
}

void World::Update(float deltaTime) {
	for (const auto& system : mSystems) {
		system->Update(deltaTime);
	}
}

void World::Render(Yuna::Core::Window* window) {
	for (const auto& system : mSystems) {
		system->Render(window);
	}
}