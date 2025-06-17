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
	mActive = true;
	mf::GUI::ClearWidgets();
	mf::GUI::Init(mWindow->GetRenderWindow());

	InitPlayButton();
	InitExitButton();

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
			mStateAction = Yuna::Core::eStateControls::EXIT;
			mActive = false;
		}
	}
}

void Menu::Render()
{
	mWindow->Clear(sf::Color::Black);
	mf::GUI::Render();
	mWindow->Display();
}

void Menu::InitPlayButton()
{
	auto playButton = UI::createButton(
		mResourceManager,
		"Play",
		sf::Vector2f(100, 100),
		sf::Vector2f(128, 64),
		[this]() {
			mStateAction = Yuna::Core::eStateControls::NEXT_STATE;
			mNextState = 2;
			mActive = false;
		}
	);
	mf::GUI::AddWidget(playButton);
}

void Menu::InitExitButton()
{
	auto exitButton = UI::createButton(
		mResourceManager,
		"Exit",
		sf::Vector2f(100, 200),
		sf::Vector2f(128, 64),
		[this]() {
			mStateAction = Yuna::Core::eStateControls::EXIT;
			mNextState = -1;
			mActive = false;
		}
	);
	mf::GUI::AddWidget(exitButton);
}