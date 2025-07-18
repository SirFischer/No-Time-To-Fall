#include "Game.hpp"

Game::Game(Yuna::Core::Window* pWindow) : Yuna::Core::State(pWindow)
{
	mStateAction = Yuna::Core::eStateControls::EXIT;
	mNextState = -1; 
}

Game::~Game()
{
	// Clean up networking to prevent hanging on shutdown
	mNetworkManager.Cleanup();
}

void Game::Init()
{
	auto gameData = GameData::getInstance();
	mActive = true;

	// Network initialization
	if (gameData.getIsServer())
	{
		mNetworkManager.SetMode(NetworkMode::HOST);
		mNetworkManager.StartServer(gameData.getServerPort());
		//main player
		mWorld.SpawnPlayer(sf::Vector2f(100.0f, 100.0f), true);
		mWorld.SpawnPlayer(sf::Vector2f(100.0f, 100.0f), false);
	}
	else
	{
		mNetworkManager.SetMode(NetworkMode::CLIENT);
		mNetworkManager.ConnectToServer(gameData.getConnectionString(), gameData.getServerPort());
		mWorld.SpawnPlayer(sf::Vector2f(100.0f, 100.0f), false);
		mWorld.SpawnPlayer(sf::Vector2f(100.0f, 100.0f), true);
	}

	
	
	// Initialize the camera
	mCamera.SetSize(sf::Vector2f(mWindow->GetSize()));
	auto cameraEntity = mWorld.CreateEntity();
	mWorld.AddComponent<TransformComponent>(cameraEntity, 0.0f, 0.0f);
	mWorld.AddComponent<VelocityComponent>(cameraEntity, 0.0f, 0.0f);

	// Initialize the world
	mWorld.AddSystem<InputSystem>(&mWorld, &mEventHandler);
	mWorld.AddSystem<NetworkSystem>(&mWorld, &mNetworkManager);
	
	if (gameData.getIsServer()) mWorld.AddSystem<GravitySystem>(&mWorld);
	mWorld.AddSystem<MovementSystem>(&mWorld);
	if (gameData.getIsServer()) mWorld.AddSystem<EntityCollisionDetectionSystem>(&mWorld);
	if (gameData.getIsServer()) mWorld.AddSystem<MapCollisionDetectionSystem>(&mWorld);
	mWorld.AddSystem<VelocitySystem>(&mWorld);

	mWorld.AddSystem<RenderSystem>(&mWorld);
	mWorld.AddSystem<CameraSystem>(&mWorld, &mCamera, cameraEntity);
	mWorld.AddSystem<RespawnSystem>(&mWorld);
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
