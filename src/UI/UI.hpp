#include "memory.h"
#include "Yuna.hpp"

class UI {
public:
	static std::shared_ptr<mf::Button> createButton(
		Yuna::Core::ResourceManager& resourceManager,
		const std::string& text,
		const sf::Vector2f& position,
		const sf::Vector2f& size,
		std::function<void()> onClick
	) {

		auto font = resourceManager.LoadFont("./assets/fonts/Roboto.ttf");
		auto texture = resourceManager.LoadTexture("./assets/textures/UI/button-small.png");

		auto button = mf::Button::Create();
		button->GetText()->SetString(text);
		button->GetText()->LoadFont(*font);
		button->GetText()->SetSize(20);
		button->GetText()->SetPos(sf::Vector2f(48, 16));
		button->GetText()->SetColor(sf::Color::White);
		button->SetSize(size);
		button->SetPosition(position);
		button->SetClickEvent(onClick);
		button->GetBackground()->SetBackground(*texture);
		button->GetBackground()->SetTextureRect(sf::IntRect(0, 0, 64, 32));

		button->AddEventListener(mf::eEvent::ENTERED, [button]() {
			button->GetBackground()->SetTextureRect(sf::IntRect(64, 0, 64, 32));
		});
		button->AddEventListener(mf::eEvent::EXITED, [button]() {
			button->GetBackground()->SetTextureRect(sf::IntRect(0, 0, 64, 32));
		});

		return button;
	}
};