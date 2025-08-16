#include "MapCollisionDetectionSystem.hpp"
#include "../../../World.hpp"
#include "../../Components/ColliderComponent.hpp"
#include "../../Components/TransformComponent.hpp"
#include "../../Components/VelocityComponent.hpp"

MapCollisionDetectionSystem::MapCollisionDetectionSystem(World* world) : mWorld(world) {}

void MapCollisionDetectionSystem::Update(float deltaTime) {
	(void)deltaTime; // Unused parameter, can be removed if not needed
	auto entities = mWorld->GetEntitiesWith<ColliderComponent, TransformComponent, VelocityComponent>();
	auto map = mWorld->GetMap();

	if (!map) {
		return; // No map loaded, nothing to check
	}

	for (EntityID entity : entities) {
		auto* collider = mWorld->GetComponent<ColliderComponent>(entity);
		auto* transform = mWorld->GetComponent<TransformComponent>(entity);
		auto* velocity = mWorld->GetComponent<VelocityComponent>(entity);

		if (collider && transform && velocity) {
			sf::FloatRect boundingBox(
				transform->x + collider->boundingBox.left,
				transform->y + collider->boundingBox.top,
				collider->boundingBox.width,
				collider->boundingBox.height
			);
			sf::Vector2f rayDir = sf::Vector2f(velocity->vx * deltaTime, velocity->vy * deltaTime);
			sf::Vector2f collisionPoint;
			sf::Vector2f collisionNormal;
			float collisionTime;
			velocity->onGround = false;
			std::vector<std::pair<sf::FloatRect, float>> collisionTimes;

			auto tiles = map->GetMapData();
			const int tileSize = static_cast<int>(map->GetTileSize());
			const int mapWidth = static_cast<int>(tiles->size());
			
			int startX = static_cast<int>(transform->x / tileSize) - 3;
			int startY = static_cast<int>(transform->y / tileSize) - 3;
			int endX = static_cast<int>(transform->x / tileSize) + 3;
			int endY = static_cast<int>(transform->y / tileSize) + 3;

			startX = std::max(0, startX);
			endX = std::min(mapWidth - 1, endX);

			for (int x = startX; x <= endX; ++x) {
				const int mapHeight = static_cast<int>((*tiles)[x].size());
				int clampedStartY = std::max(0, startY);
				int clampedEndY = std::min(mapHeight - 1, endY);
				
				for (int y = clampedStartY; y <= clampedEndY; ++y) {
					const auto& tileIDs = (*tiles)[x][y];

					if (tileIDs.empty()) {
						continue;
					}

					for (int tileID : tileIDs) {
						const auto& block = map->GetBlockDefinitions()[tileID];

						if (!block.IsSolid()) {
							continue;
						}

						if (Yuna::Physics::DynamicRectCollision(boundingBox, rayDir, sf::FloatRect(x * tileSize, y * tileSize, block.GetSize().x, block.GetSize().y), collisionPoint, collisionNormal, collisionTime)) {
							collisionTimes.push_back(std::pair<sf::FloatRect, float>(sf::FloatRect(x * tileSize, y * tileSize, block.GetSize().x, block.GetSize().y), collisionTime));
						}
					}
				}
			}

			std::sort(collisionTimes.begin(), collisionTimes.end(), [](const std::pair<sf::FloatRect, float> &a, const std::pair<sf::FloatRect, float> &b) { return a.second < b.second; });

			for (auto &collision : collisionTimes)
			{
				rayDir = sf::Vector2f(velocity->vx * deltaTime, velocity->vy * deltaTime);
				if (Yuna::Physics::DynamicRectCollision(boundingBox, rayDir, collision.first, collisionPoint, collisionNormal, collisionTime))
				{
					velocity->vx += collisionNormal.x * std::abs(velocity->vx) * (1.f - collisionTime);
					velocity->vy += collisionNormal.y * std::abs(velocity->vy) * (1.f - collisionTime);
					if (collisionNormal.y < 0.f)
					{
						velocity->onGround = true;
						velocity->vy = 0.f;
					}
				}
			}

		}
	}
}

bool MapCollisionDetectionSystem::ShouldProcessEntity(EntityID entity) {
	return mWorld->HasComponent<ColliderComponent>(entity) &&
	       mWorld->HasComponent<TransformComponent>(entity) &&
	       mWorld->HasComponent<VelocityComponent>(entity);
}
