#include "InputSystem.hpp"

#include "../../World.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/InputComponent.hpp"

InputSystem::InputSystem(World* world) : mWorld(world) {}

void InputSystem::Update(float deltaTime) {
	(void)deltaTime;
}

void InputSystem::HandleEvent(const sf::Event& event) {
	auto entities = mWorld->GetEntitiesWith<InputComponent>();

	for (EntityID entity : entities) {
		auto* input = mWorld->GetComponent<InputComponent>(entity);
		auto* transform = mWorld->GetComponent<TransformComponent>(entity);

		if (input) {
			input->Reset();
		}

		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
				case sf::Keyboard::Up:
					input->up = true;
					if (transform) {
						transform->y -= 10.0f; // Move up by 10 units
					}
					break;
				case sf::Keyboard::Down:
					input->down = true;
					if (transform) {
						transform->y += 10.0f; // Move down by 10 units
					}
					break;
				case sf::Keyboard::Left:
					input->left = true;
					if (transform) {
						transform->x -= 10.0f; // Move left by 10 units
					}
					break;
				case sf::Keyboard::Right:
					input->right = true;
					if (transform) {
						transform->x += 10.0f; // Move right by 10 units
					}
					break;
				case sf::Keyboard::Space:
					input->action = true;
					break;
				default:
					break;
			}
		} else if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code) {
				case sf::Keyboard::Up:
					input->up = false;
					break;
				case sf::Keyboard::Down:
					input->down = false;
					break;
				case sf::Keyboard::Left:
					input->left = false;
					break;
				case sf::Keyboard::Right:
					input->right = false;
					break;
				case sf::Keyboard::Space:
					input->action = false;
					break;
				default:
					break;
			}
		}

		
	}
}

bool InputSystem::ShouldProcessEntity(EntityID entity) {
	(void)entity; // Unused parameter, but kept for consistency
	return true;
}
