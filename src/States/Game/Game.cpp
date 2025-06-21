#include "Game.hpp"

Game::Game(Yuna::Core::Window* pWindow) : Yuna::Core::State(pWindow)
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

	// Initialize the camera
	mCamera.SetSize(sf::Vector2f(mWindow->GetSize()));
	// Zoom is now handled by the scaling system
	auto cameraEntity = mWorld.CreateEntity();
	mWorld.AddComponent<TransformComponent>(cameraEntity, 0.0f, 0.0f);
	mWorld.AddComponent<VelocityComponent>(cameraEntity, 0.0f, 0.0f);

	// Initialize the world
	mWorld.AddSystem<InputSystem>(&mWorld, &mEventHandler);
	mWorld.AddSystem<GravitySystem>(&mWorld);
	mWorld.AddSystem<EntityCollisionDetectionSystem>(&mWorld);
	mWorld.AddSystem<MapCollisionDetectionSystem>(&mWorld);
	mWorld.AddSystem<MovementSystem>(&mWorld);
	mWorld.AddSystem<RenderSystem>(&mWorld);
	mWorld.AddSystem<CameraSystem>(&mWorld, &mCamera, cameraEntity);
	mWorld.Init();

	// Default key bindings
	mEventHandler.BindKey(sf::Keyboard::Right, (uint32_t)eAction::MOVE_RIGHT);
	mEventHandler.BindKey(sf::Keyboard::Left, (uint32_t)eAction::MOVE_LEFT);
	mEventHandler.BindKey(sf::Keyboard::Up, (uint32_t)eAction::JUMP);
	mEventHandler.BindKey(sf::Keyboard::Down, (uint32_t)eAction::CROUCH);
}

void Game::Update()
{
	mWorld.Update(mDeltaTime);

	// FPS
	if (mFPSClock.getElapsedTime().asSeconds() >= 1.0f)
	{
		mFPSClock.restart();
		std::cout << mFPS << " FPS" << std::endl;
	}
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
		
		if (event.type == sf::Event::Resized)
		{
			mCamera.SetSize(sf::Vector2f(event.size.width, event.size.height));
		}

		mEventHandler.HandleEvent(event);
		mWorld.HandleEvent(event);
	}
}

void Game::Render()
{
	mWindow->Clear(sf::Color::Black);
	mWindow->SetView(mCamera.GetView());
	mWorld.Render(mWindow);
	mWindow->Display();
}
