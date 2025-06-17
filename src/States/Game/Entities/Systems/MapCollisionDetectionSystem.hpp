#pragma once

#include "System.hpp"

class World;
struct ColliderComponent;
struct TransformComponent;
struct VelocityComponent;

class MapCollisionDetectionSystem : public System {
private:
	World* mWorld;

public:
	MapCollisionDetectionSystem(World* world);
	void Update(float deltaTime) override;
	bool ShouldProcessEntity(EntityID entity) override;

};

