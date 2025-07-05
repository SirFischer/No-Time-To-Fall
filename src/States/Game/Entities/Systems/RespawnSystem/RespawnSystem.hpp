#pragma once

#include "../System.hpp"

class World;

class RespawnSystem : public System {
private:
    World* mWorld;

public:
    RespawnSystem(World* world);
    void Update(float deltaTime) override;
    bool ShouldProcessEntity(EntityID entity) override;
};