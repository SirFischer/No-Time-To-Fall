#include "Application.hpp"

std::unique_ptr<Yuna::Core::State>	stateFactory(uint8_t tID, Yuna::Core::Window* tWindow)
{
	switch (tID)
	{
		case 0:
			return (std::make_unique<Splash>(tWindow));
		break;
		case 1:
			return (std::make_unique<Menu>(tWindow));
		break;
		case 2:
			return (std::make_unique<Game>(tWindow));
		break;
		default:
		break;
	}
	return (nullptr);
}

Application::Application()
{
	mWindow.SetTitle("No Time To Fall");
	
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	
	sf::Vector2i windowSize;
	windowSize.x = static_cast<int>(desktop.width * 0.8f);
	windowSize.y = static_cast<int>(desktop.height * 0.8f);
	
	mWindow.SetSize(windowSize);
	mStateManager.SetStateFactory(stateFactory);
	mStateManager.SetEntryState(0);
}

Application::~Application()
{
	// Destructor implementation
}