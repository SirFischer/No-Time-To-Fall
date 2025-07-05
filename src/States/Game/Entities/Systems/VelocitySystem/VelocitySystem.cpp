#include "VelocitySystem.hpp"
#include "../../../World.hpp"
#include "../../Components/TransformComponent.hpp"
#include "../../Components/VelocityComponent.hpp"

VelocitySystem::VelocitySystem(World* world) : mWorld(world) {}

void VelocitySystem::Update(float deltaTime) {
    auto entities = mWorld->GetEntitiesWith<TransformComponent, VelocityComponent>();
    
    for (EntityID entity : entities) {
        auto* transform = mWorld->GetComponent<TransformComponent>(entity);
        auto* velocity = mWorld->GetComponent<VelocityComponent>(entity);

		if (!transform || !velocity)
		{
			continue; // Skip if any component is missing
		}
        
        transform->x += velocity->vx * deltaTime;
        transform->y += velocity->vy * deltaTime;
    }
}

bool VelocitySystem::ShouldProcessEntity(EntityID entity) {
    return mWorld->HasComponent<TransformComponent>(entity) && 
           mWorld->HasComponent<VelocityComponent>(entity);
}
