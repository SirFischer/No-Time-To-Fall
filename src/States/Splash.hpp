#pragma once
#include "Yuna.hpp"

class Splash : public Yuna::Core::State
{
	private:
		sf::Clock mDurationClock;
		sf::Time mDuration;

		sf::Texture mLogoTexture;
		sf::Sprite mLogoSprite;

	public:
		Splash(Yuna::Core::Window* pWindow);
		~Splash();

		void Init() override;
		void Update() override;
		void HandleEvents() override;
		void Render() override;

		void LoadLogo(const std::string& logoPath);
};