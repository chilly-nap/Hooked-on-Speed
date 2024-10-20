#pragma once
#include "Hookshot.h"

const float HOOKSHOT_VELOCITY = 10;

// Constructor: Initializes the hookshot with a given starting position
Hookshot::Hookshot()
{
	gX = 0;
	gY = 0;

	mVelocity.x = 0;
	mVelocity.y = 0;

	mDirection.x = 0;
	mDirection.y = 0;

	mActive = false;

	mHitbox = { 0, 0, 5, 5 };
}

// Launch the hookshot with a given velocity and direction
void Hookshot::launch(const SDL_FPoint& direction, float velocity, const SDL_FPoint& startPosition)
{
	mDirection = direction;
	mVelocity.x = velocity * mDirection.x;
	mVelocity.y = velocity * mDirection.y;

	gX = startPosition.x;
	gY = startPosition.y;

	mActive = true;
}

// Update hookshot position based on its velocity and direction
void Hookshot::update(Player& gPlayer)
{
	if (mActive)
	{
		gX += mVelocity.x;
		gY += mVelocity.y;

		mHitbox.x = static_cast<int>(gX);
		mHitbox.y = static_cast<int>(gY);

		if (checkHit())
		{
			stop();
			// Move the player to the hookshot's position
			gPlayer.setPosition(gX - (gPlayer.mCollider.w / 2) +32, gY - (gPlayer.mCollider.h / 2) + 32);
			gPlayer.mCollider.x = gPlayer.mX;
			gPlayer.mCollider.y = gPlayer.mY;
		}
		else if (gX < 0 || gX > LEVEL_WIDTH || gY < 0 || gY > LEVEL_HEIGHT)
		{
			stop();
		}
	}
}

// Check if the hookshot has hit a target (tile)
bool Hookshot::checkHit()
{
	if (touchesWall(mHitbox, tileSet))
	{
		return true;
	}
	return false;
}

// Stop the hookshot (called when the hookshot is released or hits a target)
void Hookshot::stop()
{
	mVelocity.x = 0;
	mVelocity.y = 0;
	mDirection.x = 0;
	mDirection.y = 0;
	mActive = false;
}

// Render the hookshot on screen
void Hookshot::render(int camX, int camY)
{
	if (mActive)
	{
		SDL_Rect renderQuad = {
			static_cast<int>(gX - camX),   // Subtract the camera's X offset
			static_cast<int>(gY - camY),   // Subtract the camera's Y offset
			mHitbox.w,
			mHitbox.h
		};

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &renderQuad);
	}
}

// Get the current velocity of the hookshot
SDL_FPoint Hookshot::getVelocity() const
{
	return mVelocity;
}

// Get the direction of the hookshot
SDL_FPoint Hookshot::getDirection() const
{
	return mDirection;
}

// Check if the hookshot is active (launched)
bool Hookshot::isActive() const
{
	return mActive;
}

Hookshot gHookshot = Hookshot();