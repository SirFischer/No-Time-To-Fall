#pragma once
#include "Yuna.hpp"
#include "../../UI/UI.hpp"

class ConnectionMenu : public Yuna::Core::State
{
	private:
		Yuna::Core::ResourceManager mResourceManager;

		void InitBackButton();
		
	public:
		ConnectionMenu(Yuna::Core::Window* pWindow);
		~ConnectionMenu();

		void Init() override;
		void Update() override;
		void HandleEvents() override;
		void Render() override;
};