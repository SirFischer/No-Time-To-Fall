#pragma once
#include "Yuna.hpp"

class Block
{
	private:
		sf::Vector2f mPosition;
		sf::Vector2f mSize;

		sf::Texture mTexture;
		sf::Sprite mSprite;

	public:
		Block() = default;
		virtual ~Block() = default;

		const sf::Vector2f& GetPosition() const { return mPosition; }
		void SetPosition(const sf::Vector2f& tPosition) { mPosition = tPosition; }

		const sf::Vector2f& GetSize() const { return mSize; }
		void SetSize(const sf::Vector2f& tSize) { mSize = tSize; }

		const sf::Texture& GetTexture() const { return mTexture; }
		void SetTexture(const sf::Texture& tTexture) { mTexture = tTexture; mSprite.setTexture(mTexture); }

		virtual void Update();
		virtual void Render(Yuna::Core::Window *tWindow);
};