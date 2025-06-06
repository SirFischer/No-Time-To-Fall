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
	LoadLogo("./assets/img/splash.png");

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
	mWindow->Clear(sf::Color::White);
	mWindow->Draw(mLogoSprite);
	mWindow->Display();
}

void Splash::LoadLogo(const std::string& logoPath)
{
	if (!mLogoTexture.loadFromFile(logoPath))
	{
		// Handle error
	}
	mLogoSprite.setTexture(mLogoTexture);
	mLogoSprite.setPosition(
		(mWindow->GetSize().x - mLogoTexture.getSize().x) / 2.f,
		(mWindow->GetSize().y - mLogoTexture.getSize().y) / 2.f
	);
}