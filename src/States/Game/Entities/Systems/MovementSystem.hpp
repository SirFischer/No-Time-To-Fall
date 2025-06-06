#pragma once

#include "System.hpp"

class World;
struct TransformComponent;
struct VelocityComponent;

class MovementSystem : public System {
private:
    World* mWorld;

public:
    MovementSystem(World* world);
    void Update(float deltaTime) override;
    bool ShouldProcessEntity(EntityID entity) override;
};