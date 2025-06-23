#include "MovementSystem.hpp"
#include "../../World.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/VelocityComponent.hpp"

MovementSystem::MovementSystem(World* world) : mWorld(world) {}

void MovementSystem::Update(float deltaTime) {
    auto entities = mWorld->GetEntitiesWith<TransformComponent, VelocityComponent>();
    
    for (EntityID entity : entities) {
        auto* velocity = mWorld->GetComponent<VelocityComponent>(entity);
		auto* input = mWorld->GetComponent<InputComponent>(entity);

		if (!velocity || !input)
		{
			continue; // Skip if any component is missing
		}
		
		const float acceleration = 1500.0f; // pixels/second²
		const float friction = 0.95f; // Friction coefficient
		const float maxSpeed = 3000.0f; // Maximum horizontal speed
		
		if (input->isMovingRight)
		{
			velocity->vx += acceleration * deltaTime;
		}
		else if (input->isMovingLeft)
		{
			velocity->vx -= acceleration * deltaTime;
		}
		
		velocity->vx *= friction;
		
		if (velocity->vx > maxSpeed) {
			velocity->vx = maxSpeed;
		} else if (velocity->vx < -maxSpeed) {
			velocity->vx = -maxSpeed;
		}

		if (input->isJumping && velocity->onGround) {
			velocity->vy = -200.0f; // Jump force, adjust as needed
			velocity->onGround = false; // Set to false to prevent double jumping
		}
		
    }
}

bool MovementSystem::ShouldProcessEntity(EntityID entity) {
    return mWorld->HasComponent<VelocityComponent>(entity) &&
		   mWorld->HasComponent<InputComponent>(entity);
}
