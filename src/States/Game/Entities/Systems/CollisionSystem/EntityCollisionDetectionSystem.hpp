#pragma once

#include "../System.hpp"

class World;
struct ColliderComponent;
struct TransformComponent;
struct VelocityComponent;

class EntityCollisionDetectionSystem : public System {
private:
	World* mWorld;

public:
	EntityCollisionDetectionSystem(World* world);
	void Update(float deltaTime) override;
	bool ShouldProcessEntity(EntityID entity) override;

};

