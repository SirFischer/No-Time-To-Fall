#include "CameraSystem.hpp"
#include "../../World.hpp"
#include "../../Camera/Camera.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/VelocityComponent.hpp"

CameraSystem::CameraSystem(World* world, Camera* camera, EntityID cameraEntity)
	: mWorld(world), mCamera(camera), mCameraEntity(cameraEntity) {}

void CameraSystem::Update(float deltaTime) {
	(void)deltaTime;
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
			mLinearVelocity += (mSpeed * (std::max((dist - mActiveAreaRadius) / 200.f, 1.f)));
			cameraVelocity->vx = (-dx / dist) * mLinearVelocity;
			cameraVelocity->vy = (-dy / dist) * mLinearVelocity;
			mLinearVelocity *= 0.98;
		}
		else
		{
			mLinearVelocity *= 0.90;
			cameraVelocity->vx *= 0.9;
			cameraVelocity->vy *= 0.9;
		}
	}
	
	mCamera->SetPosition(sf::Vector2f(cameraTransform->x, cameraTransform->y));
}

bool CameraSystem::ShouldProcessEntity(EntityID entity) {
	return mWorld->HasComponent<TransformComponent>(entity) &&
	       mWorld->HasComponent<VelocityComponent>(entity) &&
	       mWorld->HasComponent<CameraTargetComponent>(entity);
}
