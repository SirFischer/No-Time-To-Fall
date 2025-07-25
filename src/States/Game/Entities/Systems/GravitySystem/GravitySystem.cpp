#include "GravitySystem.hpp"
#include "../../../World.hpp"
#include "../../Components/GravityComponent.hpp"
#include "../../Components/VelocityComponent.hpp"

GravitySystem::GravitySystem(World* world) : mWorld(world) {}

void GravitySystem::Update(float deltaTime) {
	auto entities = mWorld->GetEntitiesWith<GravityComponent, VelocityComponent>();

	for (EntityID entity : entities) {
		auto* gravity = mWorld->GetComponent<GravityComponent>(entity);
		auto* velocity = mWorld->GetComponent<VelocityComponent>(entity);

		if (gravity && velocity) {

			velocity->vy += gravity->gravity *
							deltaTime *
							(velocity->vy < 0 ? 1 : gravity->fallingMultiplier);

			if (velocity->vy > gravity->terminalVelocity) {
				velocity->vy = gravity->terminalVelocity;
			}
		}
	}
}

bool GravitySystem::ShouldProcessEntity(EntityID entity) {
	return mWorld->HasComponent<GravityComponent>(entity) && 
	       mWorld->HasComponent<VelocityComponent>(entity);
}