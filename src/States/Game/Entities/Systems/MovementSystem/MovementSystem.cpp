#include "MovementSystem.hpp"
#include "../../../World.hpp"
#include "../../Components/TransformComponent.hpp"
#include "../../Components/VelocityComponent.hpp"

MovementSystem::MovementSystem(World* world) : mWorld(world) {}

void MovementSystem::Update(float deltaTime) {
    auto entities = mWorld->GetEntitiesWith<TransformComponent, VelocityComponent, JumpForceComponent, MovementSpeedComponent>();
    
    for (EntityID entity : entities) {
		auto jumpForce = mWorld->GetComponent<JumpForceComponent>(entity);
        auto* velocity = mWorld->GetComponent<VelocityComponent>(entity);
		auto* input = mWorld->GetComponent<InputComponent>(entity);
		auto* movementSpeed = mWorld->GetComponent<MovementSpeedComponent>(entity);

		if (!movementSpeed->enabled)
		{
			velocity->vx = 0;
			velocity->vy = 0;
			continue;
		}
		

		const float acceleration = (velocity->onGround ? movementSpeed->acceleration : movementSpeed->airbornAcceleration);
		const float maxSpeed = movementSpeed->maxSpeed;
		const float friction = velocity->onGround ? movementSpeed->groundFriction : movementSpeed->airFriction;
		
		bool movingHorizontally = false;
		if (input->isMovingRight)
		{
			velocity->vx += acceleration * deltaTime;
			movingHorizontally = true;
		}
		else if (input->isMovingLeft)
		{
			velocity->vx -= acceleration * deltaTime;
			movingHorizontally = true;
		}
		
		if (!movingHorizontally) {
			velocity->vx *= friction;
		}
		
		if (velocity->vx > maxSpeed) {
			velocity->vx = maxSpeed;
		} else if (velocity->vx < -maxSpeed) {
			velocity->vx = -maxSpeed;
		}

		// Jump system
		if (input->isJumping) {
			if (velocity->onGround) {
				jumpForce->isJumping = true;
				jumpForce->jumpTimer = 0.0f;
				velocity->vy = -jumpForce->jumpForce;
			}
			else if (jumpForce->isJumping && velocity->vy < 0 && jumpForce->jumpTimer < jumpForce->maxJumpTime) {
				velocity->vy -= jumpForce->extraJumpForce * deltaTime;
				jumpForce->jumpTimer += deltaTime;
			}
		}
		
		if (!input->isJumping && !velocity->onGround) {
			jumpForce->isJumping = false;
			jumpForce->jumpTimer = 0.0f;
		}
		
    }
}

bool MovementSystem::ShouldProcessEntity(EntityID entity) {
    return mWorld->HasComponent<VelocityComponent>(entity) &&
		   mWorld->HasComponent<InputComponent>(entity) &&
		   mWorld->HasComponent<JumpForceComponent>(entity) &&
		   mWorld->HasComponent<MovementSpeedComponent>(entity);
}
