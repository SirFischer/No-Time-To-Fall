#include "World.hpp"

void World::Init() {
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

EntityID World::SpawnPlayer(const sf::Vector2f position, bool isLocalPlayer) {
	EntityID playerEntity = CreateEntity();
	AddComponent<TransformComponent>(playerEntity, position.x, position.y);
	AddComponent<RenderComponent>(playerEntity, mResourceManager.LoadTexture(isLocalPlayer ? "assets/textures/player/player.png" : "assets/textures/player/player3.png"), 32, 32);
	AddComponent<VelocityComponent>(playerEntity, 0.0f, 0.0f);
	AddComponent<JumpForceComponent>(playerEntity);
	AddComponent<InputComponent>(playerEntity, isLocalPlayer);
	if (isLocalPlayer) AddComponent<CameraTargetComponent>(playerEntity);
	AddComponent<GravityComponent>(playerEntity);
	AddComponent<MovementSpeedComponent>(playerEntity);
	AddComponent<ColliderComponent>(playerEntity, sf::FloatRect(8, 0, 16, 32));
	AddComponent<NetworkComponent>(playerEntity, EntityIDGenerator::Generate(), isLocalPlayer);
	AddComponent<RespawnComponent>(playerEntity);

	return playerEntity;
}