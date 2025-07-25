#pragma once
#include "Yuna.hpp"
#include "Entities/ECS.hpp"
#include "Camera/Camera.hpp"
#include "World.hpp"
#include "../../Core/GameData.hpp"
#include "Networking/NetworkManager.hpp"

class Game : public Yuna::Core::State
{
	private:
		World mWorld;
		Camera mCamera;
		sf::Clock	mFPSClock;
		NetworkManager mNetworkManager;


	public:
		Game(Yuna::Core::Window* pWindow);
		~Game();

		void Init() override;
		void Update() override;
		void HandleEvents() override;
		void Render() override;
};