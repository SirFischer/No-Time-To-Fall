#pragma once

#include "../System.hpp"

class World;
struct GravityComponent;
struct VelocityComponent;

class GravitySystem : public System {
private:
	World* mWorld;	

public:
	GravitySystem(World* world);
	void Update(float deltaTime) override;
	bool ShouldProcessEntity(EntityID entity) override;
};