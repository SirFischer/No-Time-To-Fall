#pragma once
#include "Yuna.hpp"

class Block
{
	private:
		sf::Vector2f mPosition;
		sf::Vector2f mSize;

		sf::Texture mTexture;
		sf::Sprite mSprite;

		bool mIsSolid = true;

	public:
		Block() = default;
		// Special members now implemented in Block.cpp
		Block(const Block& other);
		Block(Block&& other) noexcept;
		Block& operator=(const Block& other);
		Block& operator=(Block&& other) noexcept;
		virtual ~Block() = default;

		bool operator==(const Block& other) const;

		const sf::Vector2f& GetPosition() const { return mPosition; }
		void SetPosition(const sf::Vector2f& tPosition) { mPosition = tPosition; }

		const sf::Vector2f& GetSize() const { return mSize; }
		void SetSize(const sf::Vector2f& tSize) { mSize = tSize; }

		const sf::Texture& GetTexture() const { return mTexture; }
		void SetTexture(const sf::Texture& tTexture) { mTexture = tTexture; mSprite.setTexture(mTexture); }

		bool IsSolid() const { return mIsSolid; }
		void SetSolid(bool tIsSolid) { mIsSolid = tIsSolid; }

		virtual void Update();
		virtual void Render(Yuna::Core::Window *tWindow);
};