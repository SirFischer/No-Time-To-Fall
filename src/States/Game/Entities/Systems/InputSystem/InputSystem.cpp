#include "InputSystem.hpp"

#include "../../../World.hpp"
#include "../../Components/TransformComponent.hpp"
#include "../../Components/InputComponent.hpp"

InputSystem::InputSystem(World* world, Yuna::Core::EventHandler* eventHandler)
	: mWorld(world), mEventHandler(eventHandler) {}

void InputSystem::Update(float deltaTime)
{
	(void)deltaTime; // Suppress unused parameter warning
	auto entities = mWorld->GetEntitiesWith<InputComponent>();

	for (EntityID entity : entities)
	{
		auto* input = mWorld->GetComponent<InputComponent>(entity);

		if (!input)
		{
			continue;
		}

		input->isMovingRight = mEventHandler->GetEventState((uint32_t)eAction::MOVE_RIGHT);
		input->isMovingLeft = mEventHandler->GetEventState((uint32_t)eAction::MOVE_LEFT);
		input->isJumping = mEventHandler->GetEventState((uint32_t)eAction::JUMP);
		input->isCrouching = mEventHandler->GetEventState((uint32_t)eAction::CROUCH);

	}
}

void InputSystem::HandleEvent(const sf::Event& event)
{
	(void)event; // Suppress unused parameter warning
}

bool InputSystem::ShouldProcessEntity(EntityID entity)
{
	return mWorld->HasComponent<InputComponent>(entity);
}
