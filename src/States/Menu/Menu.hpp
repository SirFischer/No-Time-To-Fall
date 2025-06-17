#pragma once
#include "Yuna.hpp"
#include "../../UI/UI.hpp"

class Menu : public Yuna::Core::State
{
	private:
		Yuna::Core::ResourceManager mResourceManager;

		void InitPlayButton();
		void InitExitButton();
		
	public:
		Menu(Yuna::Core::Window* pWindow);
		~Menu();

		void Init() override;
		void Update() override;
		void HandleEvents() override;
		void Render() override;
};