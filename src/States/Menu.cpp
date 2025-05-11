#include "Menu.hpp"

Menu::Menu(Yuna::Core::Window* pWindow)
	: Yuna::Core::State(pWindow)
{
	mStateAction = Yuna::Core::eStateControls::EXIT;
	mNextState = -1; 
}

Menu::~Menu()
{
	// Destructor implementation
}

void Menu::Init()
{
	mf::GUI::ClearWidgets();
	mf::GUI::Init(mWindow->GetRenderWindow());

}

void Menu::Update()
{
	
}

void Menu::HandleEvents()
{
	sf::Event event;
	while (mWindow->PollEvent(event))
	{
		mf::GUI::HandleEvent(event);
		if (event.type == sf::Event::Closed)
		{
			mWindow->GetRenderWindow()->close();
		}
	}
}

void Menu::Render()
{
	mWindow->Clear(sf::Color::Black);
	mf::GUI::Render();
	mWindow->Render();
}