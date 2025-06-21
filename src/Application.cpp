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
	mWindow.SetSize(sf::Vector2i(1920, 1080));
	mStateManager.SetStateFactory(stateFactory);
	mStateManager.SetEntryState(0);
}

Application::~Application()
{
	// Destructor implementation
}