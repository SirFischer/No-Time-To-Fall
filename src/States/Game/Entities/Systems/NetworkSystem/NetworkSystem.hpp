#pragma once

#include "../System.hpp"

class World;
class NetworkManager;
class NetworkSystem : public System {
private:
    World* mWorld;
    NetworkManager* mNetworkManager;

	void SendInput(EntityID entity);
	void SendWorldState();
	void ReceiveInput();
	void ReceiveWorldState();

public:
    NetworkSystem(World* world, NetworkManager* networkManager);
    void Update(float deltaTime) override;
    bool ShouldProcessEntity(EntityID entity) override;
};