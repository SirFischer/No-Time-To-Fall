#pragma once

#include "Component.hpp"

struct VelocityComponent : public Component {
    float vx = 0.0f;
    float vy = 0.0f;

    VelocityComponent() = default;
    VelocityComponent(float vx, float vy) : vx(vx), vy(vy) {}
};