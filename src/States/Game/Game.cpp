#include "Game.hpp"

Game::Game(Yuna::Core::Window* pWindow)
	: Yuna::Core::State(pWindow)
{
	mStateAction = Yuna::Core::eStateControls::EXIT;
	mNextState = -1; 
}

Game::~Game()
{
	// Destructor implementation
}

void Game::Init()
{
	mActive = true;

	// Initialize the world
	mWorld.AddSystem<RenderSystem>(&mWorld);
	mWorld.AddSystem<MovementSystem>(&mWorld);
	mWorld.AddSystem<InputSystem>(&mWorld);
	mWorld.Init();
}

void Game::Update()
{
	mWorld.Update(mDeltaTime);
}

void Game::HandleEvents()
{
	sf::Event event;
	while (mWindow->PollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mStateAction = Yuna::Core::eStateControls::EXIT;
			mActive = false;
		}

		mWorld.HandleEvent(event);
	}
}

void Game::Render()
{
	mWindow->Clear(sf::Color::Black);
	mWorld.Render(mWindow);
	mWindow->Display();
}
