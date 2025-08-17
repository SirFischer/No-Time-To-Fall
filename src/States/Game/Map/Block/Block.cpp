#include "Block.hpp"

// Copy constructor
Block::Block(const Block& other)
	: mPosition(other.mPosition), mSize(other.mSize), mTexture(other.mTexture), mSprite(other.mSprite), mIsSolid(other.mIsSolid)
{
	mSprite.setTexture(mTexture);
}

// Move constructor
Block::Block(Block&& other) noexcept
	: mPosition(other.mPosition), mSize(other.mSize), mTexture(std::move(other.mTexture)), mSprite(other.mSprite), mIsSolid(other.mIsSolid)
{
	mSprite.setTexture(mTexture);
}

// Copy assignment
Block& Block::operator=(const Block& other)
{
	if (this != &other)
	{
		mPosition = other.mPosition;
		mSize = other.mSize;
		mTexture = other.mTexture;
		mSprite = other.mSprite;
		mIsSolid = other.mIsSolid;
		mSprite.setTexture(mTexture);
	}
	return *this;
}

// Move assignment
Block& Block::operator=(Block&& other) noexcept
{
	if (this != &other)
	{
		mPosition = other.mPosition;
		mSize = other.mSize;
		mTexture = std::move(other.mTexture);
		mSprite = other.mSprite;
		mIsSolid = other.mIsSolid;
		mSprite.setTexture(mTexture);
	}
	return *this;
}

bool Block::operator==(const Block& other) const
{
	return  mSize == other.mSize &&
		   mTexture.getSize() == other.mTexture.getSize() &&
		   mIsSolid == other.mIsSolid && mTexture.getNativeHandle() == other.mTexture.getNativeHandle();
}

void Block::Update()
{
	// Update logic for the block can be added here
}

void Block::Render(Yuna::Core::Window *tWindow)
{
	mSprite.setPosition(mPosition);
	tWindow->Draw(mSprite);
}