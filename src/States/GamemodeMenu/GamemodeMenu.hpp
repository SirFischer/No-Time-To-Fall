#pragma once
#include "Yuna.hpp"
#include "../../UI/UI.hpp"

class GamemodeMenu : public Yuna::Core::State
{
	private:
		Yuna::Core::ResourceManager mResourceManager;

		void InitSinglePlayerButton();
		void InitMultiplayerButton();
		void InitBackButton();
		
	public:
		GamemodeMenu(Yuna::Core::Window* pWindow);
		~GamemodeMenu();

		void Init() override;
		void Update() override;
		void HandleEvents() override;
		void Render() override;
};