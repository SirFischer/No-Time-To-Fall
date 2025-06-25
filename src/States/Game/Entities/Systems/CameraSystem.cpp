#include "CameraSystem.hpp"
#include "../../World.hpp"
#include "../../Camera/Camera.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/VelocityComponent.hpp"

CameraSystem::CameraSystem(World* world, Camera* camera, EntityID cameraEntity)
	: mWorld(world), mCamera(camera), mCameraEntity(cameraEntity) {}

void CameraSystem::Update(float deltaTime) {
	auto cameraTransform = mWorld->GetComponent<TransformComponent>(mCameraEntity);
	auto cameraVelocity = mWorld->GetComponent<VelocityComponent>(mCameraEntity);
	auto entities = mWorld->GetEntitiesWith<TransformComponent, VelocityComponent, CameraTargetComponent>();

	if (entities.empty()) {
		return;
	}

	for (EntityID entity : entities) {
		auto transform = mWorld->GetComponent<TransformComponent>(entity);
		auto cameraTarget = mWorld->GetComponent<CameraTargetComponent>(entity);
		if (!cameraTarget || !cameraTarget->isActive) {
			continue;
		}
		float dx = (cameraTransform->x - transform->x);
		float dy = (cameraTransform->y - transform->y);
		float dist = std::sqrt((dx * dx) + (dy * dy));
		
		if (dist > mActiveAreaRadius)
		{
			float acceleration = mSpeed * (std::max((dist - mActiveAreaRadius) / 200.f, 1.f));
			mLinearVelocity += acceleration * deltaTime;
			
			cameraVelocity->vx = (-dx / dist) * mLinearVelocity;
			cameraVelocity->vy = (-dy / dist) * mLinearVelocity;
			
			float dampingFactor = std::pow(0.98f, deltaTime * 60.0f); // 60 FPS reference
			mLinearVelocity *= dampingFactor;
		}
		else
		{
			// Apply stronger damping when close to target
			float dampingFactor = std::pow(0.90f, deltaTime * 60.0f); // 60 FPS reference
			mLinearVelocity *= dampingFactor;
			
			float velocityDamping = std::pow(0.9f, deltaTime * 60.0f);
			cameraVelocity->vx *= velocityDamping;
			cameraVelocity->vy *= velocityDamping;
		}
	}
	
	mCamera->SetPosition(sf::Vector2f(cameraTransform->x, cameraTransform->y));
}

bool CameraSystem::ShouldProcessEntity(EntityID entity) {
	return mWorld->HasComponent<TransformComponent>(entity) &&
	       mWorld->HasComponent<VelocityComponent>(entity) &&
	       mWorld->HasComponent<CameraTargetComponent>(entity);
}
