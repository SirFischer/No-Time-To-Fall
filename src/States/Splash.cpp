#include "Splash.hpp"

Splash::Splash(Yuna::Core::Window* pWindow)
	: Yuna::Core::State(pWindow)
{
	mDuration = sf::seconds(3.f);
	mStateAction = Yuna::Core::eStateControls::REPLACE_STATE;
	mNextState = 1; // Assuming 1 is the ID for the next state
}

Splash::~Splash()
{
	// Destructor implementation
}

void Splash::Init()
{
	// Load resources, initialize variables, etc.
	mDurationClock.restart();
}

void Splash::Update()
{
	if (mDurationClock.getElapsedTime() >= mDuration)
	{
		mActive = false;
	}
}

void Splash::HandleEvents()
{
	sf::Event event;
	while (mWindow->PollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mWindow->GetRenderWindow()->close();
		}
	}
}

void Splash::Render()
{
	mWindow->Clear(sf::Color::Black);
	// Draw splash screen graphics here
	mWindow->Render();
}