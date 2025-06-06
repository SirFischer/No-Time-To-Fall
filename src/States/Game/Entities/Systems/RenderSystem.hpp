#pragma once

#include "System.hpp"

class World;
struct TransformComponent;
struct RenderComponent;

class RenderSystem : public System {
private:
    World* mWorld;

public:
    RenderSystem(World* world);
    void Update(float deltaTime) override;
    void Render(Yuna::Core::Window* window) override;
    bool ShouldProcessEntity(EntityID entity) override;
};