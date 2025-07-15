#include "LobbyMenu.hpp"

LobbyMenu::LobbyMenu(Yuna::Core::Window* pWindow)
	: Yuna::Core::State(pWindow)
{
	mStateAction = Yuna::Core::eStateControls::PREVIOUS_STATE;
	mNextState = -1; 
}

LobbyMenu::~LobbyMenu()
{
	// Destructor implementation
}

void LobbyMenu::Init()
{
	mActive = true;
	mf::GUI::ClearWidgets();
	mf::GUI::Init(mWindow->GetRenderWindow());

	InitList();
	InitTextInput();
	InitConnectButton();
	InitStartButton();
	InitBackButton();

}

void LobbyMenu::Update()
{
	
}

void LobbyMenu::HandleEvents()
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

void LobbyMenu::Render()
{
	mWindow->Clear(sf::Color::Black);
	mf::GUI::Render();
	mWindow->Display();
}

void LobbyMenu::InitTextInput()
{
	mTextInput = UI::createInputText(
		mResourceManager,
		"",
		20,
		sf::Color::White
	);
	mTextInput->SetSizePercentage(true, false);
	mTextInput->SetSize(sf::Vector2f(95, 100));
	mTextInput->SetMaxTextLength(50);

	mMenuList->AddWidget(mTextInput);
}

void LobbyMenu::InitList()
{
	mMenuList = mf::List::Create();

	sf::Vector2f windowSize = static_cast<sf::Vector2f>(mWindow->GetSize());
	sf::Vector2f listSize(800, 800);
	sf::Vector2f listPosition((windowSize.x - listSize.x) / 2, windowSize.y / 3 + 80);

	mMenuList->SetSize(listSize);
	mMenuList->SetPosition(listPosition);
	mMenuList->SetItemSpacing(5.0f);
	mMenuList->SetItemDirection(mf::eDirection::VERTICAL);
	mMenuList->SetContentOverflow(mf::List::eOverflow::NOWRAP);
	mMenuList->SetContentOffset(sf::Vector2f(5, 5));

	mf::GUI::AddWidget(mMenuList);
}

void LobbyMenu::InitConnectButton()
{
	auto connectButton = UI::createButton(
		mResourceManager,
		"Connect",
		sf::Vector2f(50, static_cast<float>(mWindow->GetSize().y) - 200),
		sf::Vector2f(128, 64),
		[this]() {
			ConnectToServer();
		}
	);
	mMenuList->AddWidget(connectButton);
}

void LobbyMenu::InitStartButton()
{
	auto startButton = UI::createButton(
		mResourceManager,
		"Start server",
		sf::Vector2f(50, static_cast<float>(mWindow->GetSize().y) - 200),
		sf::Vector2f(256, 64),
		[this]() {
			StartServer();
		}
	);
	mMenuList->AddWidget(startButton);
}

void LobbyMenu::InitBackButton()
{
	auto backButton = UI::createButton(
		mResourceManager,
		"Back",
		sf::Vector2f(50, static_cast<float>(mWindow->GetSize().y) - 100),
		sf::Vector2f(128, 64),
		[this]() {
			mStateAction = Yuna::Core::eStateControls::PREVIOUS_STATE;
			mNextState = -1;
			mActive = false;
		}
	);
	mf::GUI::AddWidget(backButton);
}

void LobbyMenu::ConnectToServer()
{
	std::string ipAddress = mTextInput->GetString();
	
	if (ipAddress.empty() || ipAddress == "Enter IP Address (e.g., 192.168.1.100)") {
		return;
	}
	GameData& gameData = GameData::getInstance();
	gameData.setServerIP(ipAddress);
	gameData.setIsServer(false);
	gameData.setServerPort(7777);
	
	mStateAction = Yuna::Core::eStateControls::REPLACE_STATE;
	mNextState = 4; // Game state
	mActive = false;
}

void LobbyMenu::StartServer()
{
	GameData& gameData = GameData::getInstance();
	gameData.setServerIP("localhost");
	gameData.setIsServer(true);
	gameData.setServerPort(7777);
	
	mStateAction = Yuna::Core::eStateControls::REPLACE_STATE;
	mNextState = 4; // Game state
	mActive = false;
}