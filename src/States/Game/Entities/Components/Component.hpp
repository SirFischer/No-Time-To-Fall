#pragma once

#include <typeindex>
#include <unordered_map>
#include <memory>

// Base component class
class Component {
public:
    virtual ~Component() = default;
};

// Component type ID system
class ComponentTypeID {
private:
    static std::size_t sNextID;

public:
    template<typename T>
    static std::size_t GetID() {
        static std::size_t id = sNextID++;
        return id;
    }
};

// Component storage for a single entity
class ComponentContainer {
private:
    std::unordered_map<std::size_t, std::unique_ptr<Component>> mComponents;

public:
    template<typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = component.get();
        mComponents[ComponentTypeID::GetID<T>()] = std::move(component);
        return *ptr;
    }

    template<typename T>
    T* GetComponent() {
        auto it = mComponents.find(ComponentTypeID::GetID<T>());
        if (it != mComponents.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    template<typename T>
    bool HasComponent() const {
        return mComponents.find(ComponentTypeID::GetID<T>()) != mComponents.end();
    }

    template<typename T>
    void RemoveComponent() {
        mComponents.erase(ComponentTypeID::GetID<T>());
    }

    void Clear() {
        mComponents.clear();
    }
};
