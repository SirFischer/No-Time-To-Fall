#include "BlockPlacementSystem.hpp"
#include "../../../World.hpp"
#include "../../../Camera/Camera.hpp"
#include "../../Components/TransformComponent.hpp"
#include "../../Components/VelocityComponent.hpp"

BlockPlacementSystem::BlockPlacementSystem(World* world)
	: mWorld(world) {}

void BlockPlacementSystem::Update(float deltaTime) {
	
	auto entities = mWorld->GetEntitiesWith<BlockPlacementComponent, InputComponent>();

	for (EntityID entity : entities)
	{
		auto* blockPlacement = mWorld->GetComponent<BlockPlacementComponent>(entity);
		auto* input = mWorld->GetComponent<InputComponent>(entity);

		if (blockPlacement->currentCooldown > sf::Time::Zero)
		{
			blockPlacement->currentCooldown -= sf::seconds(deltaTime);
		}

		if (blockPlacement->currentCooldown <= sf::Time::Zero && input->isPlacingBlock)
		{
			// Place the block
			Block block;
			block.SetSize(sf::Vector2f(32, 32));
			block.SetPosition(sf::Vector2f(10, 3));
			block.SetTexture(*mWorld->GetResourceManager()->LoadTexture("assets/textures/blocks/top.png"));
		
			mWorld->GetMap()->AddBlock(block, sf::Vector2i(10, 3));
			blockPlacement->currentCooldown = blockPlacement->placementCooldown;
		} else if (blockPlacement->currentCooldown <= sf::Time::Zero && input->isPlacingGhostBlock)
		{
			// Place the ghost block
			blockPlacement->currentCooldown = blockPlacement->ghostPlacementCooldown;
		}
	}
}

bool BlockPlacementSystem::ShouldProcessEntity(EntityID entity) {
	return mWorld->HasComponent<BlockPlacementComponent>(entity);
}
