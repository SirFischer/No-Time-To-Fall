#pragma once
#include "Yuna.hpp"

class Menu : public Yuna::Core::State
{
	private:
		
	public:
		Menu(Yuna::Core::Window* pWindow);
		~Menu();

		void Init() override;
		void Update() override;
		void HandleEvents() override;
		void Render() override;
};