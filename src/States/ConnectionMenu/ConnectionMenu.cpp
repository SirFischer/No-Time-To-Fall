#include "ConnectionMenu.hpp"

ConnectionMenu::ConnectionMenu(Yuna::Core::Window* pWindow)
	: Yuna::Core::State(pWindow)
{
	mStateAction = Yuna::Core::eStateControls::PREVIOUS_STATE;
	mNextState = -1; 
}

ConnectionMenu::~ConnectionMenu()
{
	// Destructor implementation
}

void ConnectionMenu::Init()
{
	mActive = true;
	mf::GUI::ClearWidgets();
	mf::GUI::Init(mWindow->GetRenderWindow());

	InitBackButton();

}

void ConnectionMenu::Update()
{
	
}

void ConnectionMenu::HandleEvents()
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

void ConnectionMenu::Render()
{
	mWindow->Clear(sf::Color::Black);
	mf::GUI::Render();
	mWindow->Display();
}

void ConnectionMenu::InitBackButton()
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