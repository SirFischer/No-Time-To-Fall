#include "RenderSystem.hpp"
#include "../../../World.hpp"
#include "../../Components/TransformComponent.hpp"
#include "../../Components/RenderComponent.hpp"

RenderSystem::RenderSystem(World *world) : mWorld(world) {}

void RenderSystem::Update(float deltaTime)
{
	(void)deltaTime;
}

void RenderSystem::Render(Yuna::Core::Window *window)
{
	auto entities = mWorld->GetEntitiesWith<TransformComponent, RenderComponent>();

	for (EntityID entity : entities)
	{
		auto *transform = mWorld->GetComponent<TransformComponent>(entity);
		auto *render = mWorld->GetComponent<RenderComponent>(entity);

		if (transform && render && render->visible)
		{

			render->sprite.setPosition(transform->x, transform->y);
			window->Draw(render->sprite);
		}
	}
}

bool RenderSystem::ShouldProcessEntity(EntityID entity)
{
	return mWorld->HasComponent<TransformComponent>(entity) &&
		   mWorld->HasComponent<RenderComponent>(entity);
}
