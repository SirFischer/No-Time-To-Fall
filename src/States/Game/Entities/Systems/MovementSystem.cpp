#include "MovementSystem.hpp"
#include "../../World.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/VelocityComponent.hpp"

MovementSystem::MovementSystem(World* world) : mWorld(world) {}

void MovementSystem::Update(float deltaTime) {
	(void)deltaTime; 
    auto entities = mWorld->GetEntitiesWith<TransformComponent, VelocityComponent>();
    
    for (EntityID entity : entities) {
        auto* transform = mWorld->GetComponent<TransformComponent>(entity);
        auto* velocity = mWorld->GetComponent<VelocityComponent>(entity);
        
        if (transform && velocity) {
            transform->x += velocity->vx;
            transform->y += velocity->vy;
        }
    }
}

bool MovementSystem::ShouldProcessEntity(EntityID entity) {
    return mWorld->HasComponent<TransformComponent>(entity) && 
           mWorld->HasComponent<VelocityComponent>(entity);
}
