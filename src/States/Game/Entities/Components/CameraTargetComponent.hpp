#pragma once

#include "Component.hpp"
#include <SFML/Graphics/View.hpp>

struct CameraTargetComponent : public Component {
	bool isActive = true; // Indicates if this entity should be the camera target
	
	CameraTargetComponent() = default;
};