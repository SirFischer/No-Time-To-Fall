#include "Block.hpp"


void Block::Update()
{
	// Update logic for the block can be added here
}

void Block::Render(Yuna::Core::Window *tWindow)
{
	mSprite.setPosition(mPosition);
	tWindow->Draw(mSprite);
}

bool Block::operator==(const Block& other) const
{
	return mPosition == other.mPosition &&
		   mSize == other.mSize &&
		   mTexture.getSize() == other.mTexture.getSize() &&
		   mIsSolid == other.mIsSolid;
}