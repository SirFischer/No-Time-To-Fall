#pragma once

#include <SFML/Window.hpp>

#include "Yuna.hpp"
#include "../Entity.hpp"


class System {
public:
    virtual ~System() = default;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(Yuna::Core::Window* window) { (void)window; }
    virtual void HandleEvent(const sf::Event& event) { (void)event; }

    // Override this to specify which components this system requires
    virtual bool ShouldProcessEntity(EntityID entity) = 0;
};
