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
#include "Components/CameraTargetComponent.hpp"
#include "Components/JumpForceComponent.hpp"
#include "Components/MovementSpeedComponent.hpp"
#include "Components/RespawnComponent.hpp"

// Systems
#include "Systems/RenderSystem/RenderSystem.hpp"
#include "Systems/MovementSystem/MovementSystem.hpp"
#include "Systems/InputSystem/InputSystem.hpp"
#include "Systems/GravitySystem/GravitySystem.hpp"
#include "Systems/CollisionSystem/EntityCollisionDetectionSystem.hpp"
#include "Systems/CollisionSystem/MapCollisionDetectionSystem.hpp"
#include "Systems/CameraSystem/CameraSystem.hpp"
#include "Systems/VelocitySystem/VelocitySystem.hpp"
#include "Systems/RespawnSystem/RespawnSystem.hpp"