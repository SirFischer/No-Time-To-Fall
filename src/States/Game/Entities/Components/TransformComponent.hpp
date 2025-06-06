#pragma once
#include "Component.hpp"

struct TransformComponent : public Component {
    float x = 0.0f;
    float y = 0.0f;
    float rotation = 0.0f;
    float scaleX = 1.0f;
    float scaleY = 1.0f;

    TransformComponent() = default;
    TransformComponent(float x, float y) : x(x), y(y) {}
    TransformComponent(float x, float y, float rotation) : x(x), y(y), rotation(rotation) {}
};
