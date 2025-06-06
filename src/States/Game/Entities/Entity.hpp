#pragma once

#include <cstdint>

using EntityID = std::uint32_t;

class EntityIDGenerator {
private:
    static EntityID sNextID;

public:
    static EntityID Generate() {
        return sNextID++;
    }
};
