#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>
#include <SFML/Window.hpp>

#include "Yuna.hpp"
#include "Entities/ECS.hpp"

class World {
private:
	Yuna::Core::ResourceManager mResourceManager;
    std::unordered_map<EntityID, ComponentContainer> mEntityComponents;
    std::vector<std::unique_ptr<System>> mSystems;
    std::vector<EntityID> mEntities;

public:
    EntityID CreateEntity() {
        EntityID entity = EntityIDGenerator::Generate();
        mEntities.push_back(entity);
        mEntityComponents[entity] = ComponentContainer();
        return entity;
    }

    void DestroyEntity(EntityID entity) {
        // Remove from entities list
        auto it = std::find(mEntities.begin(), mEntities.end(), entity);
        if (it != mEntities.end()) {
            mEntities.erase(it);
        }
        
        // Remove all components
        mEntityComponents.erase(entity);
    }

    bool IsEntityValid(EntityID entity) const {
        return mEntityComponents.find(entity) != mEntityComponents.end();
    }

    const std::vector<EntityID>& GetEntities() const {
        return mEntities;
    }

    // Component management
    template<typename T, typename... Args>
    T& AddComponent(EntityID entity, Args&&... args) {
        if (!IsEntityValid(entity)) {
            throw std::runtime_error("Entity does not exist");
        }
        return mEntityComponents[entity].AddComponent<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    T* GetComponent(EntityID entity) {
        if (!IsEntityValid(entity)) {
            return nullptr;
        }
        return mEntityComponents[entity].GetComponent<T>();
    }

    template<typename T>
    bool HasComponent(EntityID entity) const {
        auto it = mEntityComponents.find(entity);
        if (it == mEntityComponents.end()) {
            return false;
        }
        return it->second.HasComponent<T>();
    }

    template<typename T>
    void RemoveComponent(EntityID entity) {
        if (IsEntityValid(entity)) {
            mEntityComponents[entity].RemoveComponent<T>();
        }
    }

    template<typename T, typename... Args>
    T* AddSystem(Args&&... args) {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = system.get();
        mSystems.push_back(std::move(system));
        return ptr;
    }

    template<typename... Components>
    std::vector<EntityID> GetEntitiesWith() {
		std::vector<EntityID> result;
        for (EntityID entity : mEntities) {
			if ((HasComponent<Components>(entity) && ...)) {
				result.push_back(entity);
            }
        }
        return result;
    }

	void Init();

	void Update(float deltaTime);

	void Render(Yuna::Core::Window* window);

	void HandleEvent(const sf::Event& event);
};
