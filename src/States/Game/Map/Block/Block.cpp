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
