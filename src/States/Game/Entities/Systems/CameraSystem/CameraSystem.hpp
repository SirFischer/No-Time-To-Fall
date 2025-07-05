#pragma once

#include "Yuna.hpp"
#include "../System.hpp"

class World;
class Camera;

class CameraSystem : public System {
private:
	World* mWorld;
	Camera* mCamera;
	EntityID mCameraEntity;

	float mSpeed = 400.f;
	float mLinearVelocity = 0.0f;
	float mActiveAreaRadius = 75.0f; // Radius around the camera target to consider for movement

public:
	CameraSystem(World* world, Camera* camera, EntityID cameraEntity);

	void Update(float deltaTime) override;
	bool ShouldProcessEntity(EntityID entity) override;

};
		