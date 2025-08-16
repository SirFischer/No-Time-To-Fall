#pragma once

#include "Yuna.hpp"
#include "../System.hpp"

class World;
class Camera;

class BlockPlacementSystem : public System {
private:
	World* mWorld;

public:
	BlockPlacementSystem(World* world);

	void Update(float deltaTime) override;
	bool ShouldProcessEntity(EntityID entity) override;
};
		