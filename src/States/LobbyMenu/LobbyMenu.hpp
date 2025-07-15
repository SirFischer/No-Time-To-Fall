#pragma once
#include "Yuna.hpp"
#include "../../UI/UI.hpp"
#include "../../Core/GameData.hpp"

class LobbyMenu : public Yuna::Core::State
{
	private:
		Yuna::Core::ResourceManager mResourceManager;

		std::shared_ptr<mf::List>	mMenuList;
		std::shared_ptr<mf::Text>	mTextInput;

		void InitList();
		void InitTextInput();
		void InitConnectButton();
		void InitStartButton();
		void InitBackButton();
		
		void ConnectToServer();
		void StartServer();
		
	public:
		LobbyMenu(Yuna::Core::Window* pWindow);
		~LobbyMenu();

		void Init() override;
		void Update() override;
		void HandleEvents() override;
		void Render() override;
};