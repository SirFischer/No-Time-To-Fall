#pragma once

// Core ECS files
#include "Entity.hpp"
#include "Components/Component.hpp"
#include "Systems/System.hpp"

// Components
#include "Components/TransformComponent.hpp"
#include "Components/VelocityComponent.hpp"
#include "Components/RenderComponent.hpp"
#include "Components/InputComponent.hpp"
#include "Components/GravityComponent.hpp"
#include "Components/ColliderComponent.hpp"

// Systems
#include "Systems/RenderSystem.hpp"
#include "Systems/MovementSystem.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/GravitySystem.hpp"
#include "Systems/EntityCollisionDetectionSystem.hpp"
#include "Systems/MapCollisionDetectionSystem.hpp"