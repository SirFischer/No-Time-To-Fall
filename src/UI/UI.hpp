#include "memory.h"
#include "Yuna.hpp"

class UI {
public:
	static std::shared_ptr<mf::Button> createButton(
		const std::string& text,
		const std::string& fontPath,
		const sf::Vector2f& position,
		const sf::Vector2f& size,
		std::function<void()> onClick
	) {
		auto button = mf::Button::Create();
		button->GetText()->SetString(text);
		button->GetText()->LoadFont(fontPath);
		button->GetText()->SetSize(20);
		button->GetText()->SetPos(sf::Vector2f(0, 0));
		button->GetText()->SetColor(sf::Color::White);
		button->SetSize(size);
		button->SetPosition(position);
		button->SetClickEvent(onClick);
		button->GetBackground()->SetBackground(sf::Color::Red);

		button->AddEventListener(mf::eEvent::ENTERED, [button]() {
			button->GetBackground()->SetBackground(sf::Color(255, 0, 0, 150));
		});
		button->AddEventListener(mf::eEvent::EXITED, [button]() {
			button->GetBackground()->SetBackground(sf::Color::Red);
		});

		return button;
	}
};