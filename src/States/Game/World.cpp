#include "World.hpp"

void World::Init() {
	//test entity
	EntityID testEntity = CreateEntity();
	AddComponent<TransformComponent>(testEntity, 100.0f, 100.0f);
	AddComponent<RenderComponent>(testEntity, mResourceManager.LoadTexture("assets/textures/blocks/top.png"), 32, 32);
	AddComponent<VelocityComponent>(testEntity, 0.0f, 0.0f);
	AddComponent<JumpForceComponent>(testEntity);
	AddComponent<InputComponent>(testEntity);
	AddComponent<GravityComponent>(testEntity);
	AddComponent<MovementSpeedComponent>(testEntity);
	AddComponent<ColliderComponent>(testEntity, sf::FloatRect(0, 0, 32, 32));
	AddComponent<CameraTargetComponent>(testEntity);
	AddComponent<RespawnComponent>(testEntity);

	//test entity2
	EntityID testEntity2 = CreateEntity();
	AddComponent<TransformComponent>(testEntity2, 300.0f, 300.0f);
	AddComponent<RenderComponent>(testEntity2, mResourceManager.LoadTexture("assets/textures/Dog.png"), 32, 32);
	AddComponent<VelocityComponent>(testEntity2, 0.0f, 0.0f);
	AddComponent<GravityComponent>(testEntity2);
	AddComponent<ColliderComponent>(testEntity2, sf::FloatRect(0, 0, 32, 32));

	// Map initialization
	mMap.LoadMap(mResourceManager, "assets/maps/main.map");

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

	mMap.Render(window, sf::IntRect(0, 0, window->GetSize().x, window->GetSize().y));
}