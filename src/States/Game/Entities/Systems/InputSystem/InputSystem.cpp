#include "InputSystem.hpp"

#include "../../../World.hpp"
#include "../../Components/TransformComponent.hpp"
#include "../../Components/InputComponent.hpp"
#include "../../Components/CameraTargetComponent.hpp"

InputSystem::InputSystem(World* world, Yuna::Core::EventHandler* eventHandler, Yuna::Core::Window* window)
	: mWorld(world), mEventHandler(eventHandler), mWindow(window) {}

void InputSystem::Update(float deltaTime)
{
	(void)deltaTime; // Suppress unused parameter warning
	auto entities = mWorld->GetEntitiesWith<InputComponent>();

	for (EntityID entity : entities)
	{
		auto* input = mWorld->GetComponent<InputComponent>(entity);

		if (!input->enabled) {
			continue;
		}

		input->isMovingRight = mEventHandler->GetEventState((uint32_t)eAction::MOVE_RIGHT);
		input->isMovingLeft = mEventHandler->GetEventState((uint32_t)eAction::MOVE_LEFT);
		input->isJumping = mEventHandler->GetEventState((uint32_t)eAction::JUMP);
		input->isCrouching = mEventHandler->GetEventState((uint32_t)eAction::CROUCH);
		input->isPlacingBlock = mEventHandler->GetEventState((uint32_t)eAction::PLACE_BLOCK); mEventHandler->SetEventState((uint32_t)eAction::PLACE_BLOCK, false);
		input->isPlacingGhostBlock = mEventHandler->GetEventState((uint32_t)eAction::PLACE_GHOST_BLOCK); mEventHandler->SetEventState((uint32_t)eAction::PLACE_GHOST_BLOCK, false);

		input->mousePosition = mEventHandler->GetMousePosition();
		input->worldMousePosition = mWindow->GetViewMousePos();

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
