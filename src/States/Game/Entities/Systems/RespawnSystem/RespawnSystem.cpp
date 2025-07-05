#include "RespawnSystem.hpp"
#include "../../../World.hpp"
#include <cmath>

RespawnSystem::RespawnSystem(World* world) : mWorld(world) {}

void RespawnSystem::Update(float deltaTime) {
    auto entities = mWorld->GetEntitiesWith<TransformComponent, RespawnComponent, MovementSpeedComponent>();
    
    for (EntityID entity : entities) {
		auto *transform = mWorld->GetComponent<TransformComponent>(entity);
		auto *respawn = mWorld->GetComponent<RespawnComponent>(entity);
		auto *movement = mWorld->GetComponent<MovementSpeedComponent>(entity);

		//test
		if (transform->y > 1000) {
			respawn->respawn = true;
			auto possibleSafePosition = mWorld->GetMap()->GetNearestSafePosition(sf::Vector2f(transform->x, transform->y));
			if (possibleSafePosition != sf::Vector2f(transform->x, transform->y)) {
				respawn->lastSafePosition = possibleSafePosition;
			}
		}

		if (respawn->respawn) {
			transform->x = respawn->lastSafePosition.x;
			transform->y = respawn->lastSafePosition.y;

			movement->enabled = false;
			respawn->isRespawning = true;
			respawn->respawn = false; //reset respawn flag
		}

		if (respawn->isRespawning) {
			respawn->respawnClock += deltaTime;
			if (respawn->respawnClock >= respawn->respawnTime) {
				respawn->isRespawning = false;
				movement->enabled = true;
				respawn->respawnClock = 0.0f;
			}
		}
	}
}

bool RespawnSystem::ShouldProcessEntity(EntityID entity) {
    return	mWorld->HasComponent<RespawnComponent>(entity) &&
			mWorld->HasComponent<TransformComponent>(entity) &&
			mWorld->HasComponent<MovementSpeedComponent>(entity);
}
