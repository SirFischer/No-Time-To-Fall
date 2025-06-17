#include "InputSystem.hpp"

#include "../../World.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/InputComponent.hpp"

InputSystem::InputSystem(World* world, Yuna::Core::EventHandler* eventHandler)
	: mWorld(world), mEventHandler(eventHandler) {}

void InputSystem::Update(float deltaTime) {
	auto entities = mWorld->GetEntitiesWith<InputComponent>();

	for (EntityID entity : entities) {
		auto* velocity = mWorld->GetComponent<VelocityComponent>(entity);

		if (!velocity) {
			continue;
		}

		if (mEventHandler->GetEventState((uint32_t)eAction::MOVE_RIGHT)) {
			velocity->vx += 50.0f * deltaTime;
		}

		if (mEventHandler->GetEventState((uint32_t)eAction::MOVE_LEFT)) {
			velocity->vx -= 50.0f * deltaTime;
		}

		if (mEventHandler->GetEventState((uint32_t)eAction::JUMP)) {
			velocity->vy -= 20.0f * deltaTime;
		}

		if (mEventHandler->GetEventState((uint32_t)eAction::CROUCH)) {
			velocity->vy += 20.0f * deltaTime;
		}
	}
}

void InputSystem::HandleEvent(const sf::Event& event) {
	(void)event; // Suppress unused parameter warning
}

bool InputSystem::ShouldProcessEntity(EntityID entity) {
	return mWorld->HasComponent<InputComponent>(entity) &&
		   mWorld->HasComponent<VelocityComponent>(entity);
}
