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

		if (blockPlacement->currentCooldown > sf::Time::Zero || (!input->isPlacingBlock && !input->isPlacingGhostBlock))
		{
			continue;
		}
		
		Block block;
		block.SetSize(sf::Vector2f(32, 32));
		block.SetTexture(*mWorld->GetResourceManager()->LoadTexture("assets/textures/blocks/top.png"));

		if (input->isPlacingBlock)
		{
			block.SetSolid(true);
			blockPlacement->currentCooldown = blockPlacement->placementCooldown;
		} else if (input->isPlacingGhostBlock)
		{
			block.SetSolid(false);
			blockPlacement->currentCooldown = blockPlacement->ghostPlacementCooldown;
		}

		mWorld->GetMap()->AddBlock(block, sf::Vector2i(input->worldMousePosition.x / mWorld->GetMap()->GetTileSize(), input->worldMousePosition.y / mWorld->GetMap()->GetTileSize()));
		input->isPlacingGhostBlock = false;
		input->isPlacingBlock = false;
	}
}

bool BlockPlacementSystem::ShouldProcessEntity(EntityID entity) {
	return mWorld->HasComponent<BlockPlacementComponent>(entity);
}
