#pragma once

#include "Component.hpp"
#include <cstdint>

// Simple network component for entity identification across sessions
struct NetworkComponent : public Component {
    uint32_t networkId;
    bool isLocalPlayer;
    
    NetworkComponent(uint32_t netId = 0, bool isLocal = false) 
        : networkId(netId), isLocalPlayer(isLocal) {}
};
