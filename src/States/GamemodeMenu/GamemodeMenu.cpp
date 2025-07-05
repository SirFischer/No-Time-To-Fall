#include "GamemodeMenu.hpp"

GamemodeMenu::GamemodeMenu(Yuna::Core::Window* pWindow)
	: Yuna::Core::State(pWindow)
{
	mStateAction = Yuna::Core::eStateControls::PREVIOUS_STATE;
	mNextState = -1; 
}

GamemodeMenu::~GamemodeMenu()
{
	// Destructor implementation
}

void GamemodeMenu::Init()
{
	mActive = true;
	mf::GUI::ClearWidgets();
	mf::GUI::Init(mWindow->GetRenderWindow());

	InitSinglePlayerButton();
	InitMultiplayerButton();
	InitBackButton();

}

void GamemodeMenu::Update()
{
	
}

void GamemodeMenu::HandleEvents()
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

void GamemodeMenu::Render()
{
	mWindow->Clear(sf::Color::Black);
	mf::GUI::Render();
	mWindow->Display();
}

void GamemodeMenu::InitSinglePlayerButton()
{
	auto singlePlayerButton = UI::createButton(
		mResourceManager,
		"Single Player",
		sf::Vector2f(100, 100),
		sf::Vector2f(192, 64),
		[this]() {
			mStateAction = Yuna::Core::eStateControls::NEXT_STATE;
			mNextState = 4;
			mActive = false;
		}
	);
	mf::GUI::AddWidget(singlePlayerButton);
}

void GamemodeMenu::InitMultiplayerButton()
{
	auto multiplayerButton = UI::createButton(
		mResourceManager,
		"Multiplayer",
		sf::Vector2f(100, 200),
		sf::Vector2f(192, 64),
		[this]() {
			mStateAction = Yuna::Core::eStateControls::NEXT_STATE;
			mNextState = 3;
			mActive = false;
		}
	);
	mf::GUI::AddWidget(multiplayerButton);
}

void GamemodeMenu::InitBackButton()
{
	auto backButton = UI::createButton(
		mResourceManager,
		"Back",
		sf::Vector2f(100, 300),
		sf::Vector2f(128, 64),
		[this]() {
			mStateAction = Yuna::Core::eStateControls::PREVIOUS_STATE;
			mNextState = -1;
			mActive = false;
		}
	);
	mf::GUI::AddWidget(backButton);
}