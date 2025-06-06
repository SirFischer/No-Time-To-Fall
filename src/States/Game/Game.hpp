#pragma once
#include "Yuna.hpp"
#include "Entities/ECS.hpp"
#include "World.hpp"

class Game : public Yuna::Core::State
{
	private:
		World mWorld;

	public:
		Game(Yuna::Core::Window* pWindow);
		~Game();

		void Init() override;
		void Update() override;
		void HandleEvents() override;
		void Render() override;
};