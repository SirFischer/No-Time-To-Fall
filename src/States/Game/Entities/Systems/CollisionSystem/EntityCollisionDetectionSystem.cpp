#include "EntityCollisionDetectionSystem.hpp"
#include "../../../World.hpp"
#include "../../Components/ColliderComponent.hpp"
#include "../../Components/TransformComponent.hpp"
#include "../../Components/VelocityComponent.hpp"

EntityCollisionDetectionSystem::EntityCollisionDetectionSystem(World* world) : mWorld(world) {}

void EntityCollisionDetectionSystem::Update(float deltaTime) {
	(void)deltaTime; // Unused parameter, can be removed if not needed
	auto entities = mWorld->GetEntitiesWith<ColliderComponent, TransformComponent, VelocityComponent>();

	for (EntityID entity : entities) {
		auto* collider = mWorld->GetComponent<ColliderComponent>(entity);
		auto* transform = mWorld->GetComponent<TransformComponent>(entity);
		auto* velocity = mWorld->GetComponent<VelocityComponent>(entity);

		if (collider && transform && velocity) {
			for (EntityID otherEntity : entities) {
				if (otherEntity == entity) continue;

				auto* otherCollider = mWorld->GetComponent<ColliderComponent>(otherEntity);
				if (otherCollider && collider->boundingBox.intersects(otherCollider->boundingBox)) {
					collider->isTrigger = true;
					otherCollider->isTrigger = true;
				} else {
					collider->isTrigger = false;
					otherCollider->isTrigger = false;
				}
			}
		}
	}
}

bool EntityCollisionDetectionSystem::ShouldProcessEntity(EntityID entity) {
	return mWorld->HasComponent<ColliderComponent>(entity) &&
	       mWorld->HasComponent<TransformComponent>(entity) &&
	       mWorld->HasComponent<VelocityComponent>(entity);
}
