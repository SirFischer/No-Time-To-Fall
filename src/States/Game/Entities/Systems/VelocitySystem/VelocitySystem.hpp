#pragma once

#include "../System.hpp"

class World;
struct TransformComponent;
struct VelocityComponent;

class VelocitySystem : public System {
private:
    World* mWorld;

public:
    VelocitySystem(World* world);
    void Update(float deltaTime) override;
    bool ShouldProcessEntity(EntityID entity) override;
};