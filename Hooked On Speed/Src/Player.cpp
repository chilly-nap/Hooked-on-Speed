#pragma once

#include "Player.h"

// Constants
const int GRAVITY = 1;
const int JUMP_VELOCITY = 15;
const int MAX_VELOCITY = 10;
const int ACCELERATION = 1;
const int DASH_VELOCITY = 30;
const int DASH_DURATION = 10;
const int DASH_COOLDOWN = 30;
const int TERMINAL_VELOCITY = 5;

int frame;
int frameCounter = 0;
const int FRAME_DELAY = 5;  // Number of updates before changing the animation frame

// Constructor to initialize the player
Player::Player(int x, int y)
{
	TextureManager& textureManager = TextureManager::getInstance();
	// Set initial position using inherited mX and mY
	mX = x;
	mY = y;

	// Initialize velocity
	mVelocity.x = 0;
	mVelocity.y = 0;

	// Initialize movement and dash states
	isMoving = false;
	isDashing = false;
	canJump = true;
	dashTime = 0;
	dashCooldown = 0;
	lastDirection = 0;

	// Determine if the player is initially in the air
	mInAir = true;
	mLevelComplete = false;

	mTexture = textureManager.getIdleTexture();
	mCollider.w = textureManager.getIdleClips()[0].w;
	mCollider.h = textureManager.getIdleClips()[0].h;
	mCollider.x = 0;
	mCollider.y = 0;

	frame = 0;
}

// Destructor to free resources
Player::~Player()
{
	mTexture.freeTexture();
}

bool Player::getEndLevel()
{
	return mLevelComplete;
}

void Player::update()
{
	TextureManager& textureManager = TextureManager::getInstance();

	// Check for collision with the end level box
	if (checkCollision(mCollider, textureManager.getEndLevelBox()))
	{
		// End the level, reset position and velocity
		mLevelComplete = true;
		mVelocity.x = 0;
		mVelocity.y = 0;
		mX = 0;
		mY = 0;
		mCollider.x = mX;
		mCollider.y = mY;

		// Stop player movement and reset direction
		isMoving = false;
		lastDirection = 0;
	}
	else
	{
		// Continue the level if no collision with the end box
		mLevelComplete = false;
	}

	// Update player state depending on whether the player is dashing or moving
	if (isDashing)
	{
		updateDash();  // Update dash state if dashing
	}
	else
	{
		updateMovement();  // Handle normal movement if not dashing
		applyGravity();     // Apply gravity when not dashing
		constrainToScreen(); // Ensure the player stays within screen bounds
	}

	// Increment the frame counter for animation
	frameCounter++;

	// Update the frame for animation once the delay is reached
	if (frameCounter >= FRAME_DELAY)
	{
		frame++;
		frameCounter = 0;  // Reset the frameCounter after the frame updates
	}

	// Loop the animation frames if needed
	if (frame / 10 >= 10)
	{
		frame = 0;
	}
}

void Player::updateMovement() {
	// Handle cooldown
	if (dashCooldown > 0) {
		dashCooldown--;
	}

	// X motion
	if (isMoving) {
		accelerate();
		mX += mVelocity.x;

		// Check for X-axis collisions
		mCollider.x = mX;
		if (touchesWall(mCollider, tileSet)) {
			// Undo X movement if collision detected
			mX -= mVelocity.x;
			mCollider.x = mX;
			mVelocity.x = 0;
		}
	}

	// Y motion
	mY += mVelocity.y;
	mCollider.y = mY;

	// Check for Y-axis collisions
	if (touchesWall(mCollider, tileSet)) {
		// Undo Y movement if collision detected
		mY -= mVelocity.y;
		mCollider.y = mY;
		mVelocity.y = 0;

		// Allow jumping again when on the ground
		if (mVelocity.y > 0) { // Colliding while falling
			canJump = true;
			mInAir = false;
		}
	}
	else {
		mInAir = true; // Player is in the air if no collision on Y-axis
	}
}

void Player::accelerate()
{
	if (lastDirection == -1 && mVelocity.x > -MAX_VELOCITY)
	{
		mVelocity.x -= ACCELERATION;
	}
	else if (lastDirection == 1 && mVelocity.x < MAX_VELOCITY)
	{
		mVelocity.x += ACCELERATION;
	}
}

void Player::startDash()
{
	if (dashCooldown <= 0 && !isDashing)
	{
		isDashing = true;
		dashTime = DASH_DURATION;
		mVelocity.x = (lastDirection == 1) ? DASH_VELOCITY : -DASH_VELOCITY;
		canJump = false; // Disable jumping during dash
		AudioManager::getInstance().playDashEffect();
	}
}

void Player::updateDash()
{
	// Reduce dash time on each update
	dashTime--;

	// End dash when the time runs out
	if (dashTime <= 0)
	{
		endDash();
	}

	// Apply dash velocity to the player's position
	mX += mVelocity.x;

	// Ensure the player stays within horizontal bounds
	constrainToScreenX();

	// Update the player's collider to match the new position
	mCollider.x = mX;

	// Keep the player airborne during the dash
	mInAir = true;
	applyGravity();  // Gravity still affects the player even during a dash
}

void Player::endDash()
{
	// End the dash and reset dash-related variables
	isDashing = false;
	dashCooldown = DASH_COOLDOWN;

	// Stop the player's horizontal movement after the dash ends
	mVelocity.x = 0;
}

void Player::applyGravity() {
	// Apply gravity if the player is in the air
	if (mInAir) {
		mVelocity.y += GRAVITY;

		// Clamp the falling speed to terminal velocity
		if (mVelocity.y > TERMINAL_VELOCITY) {
			mVelocity.y = TERMINAL_VELOCITY;
		}

		// Move player down by velocity and check for collisions
		mY += mVelocity.y;
		mCollider.y = mY;

		if (touchesWall(mCollider, tileSet)) {
			// Undo Y movement if collision detected
			mY -= mVelocity.y;
			mCollider.y = mY;
			mVelocity.y = 0;

			// Allow jumping again when on the ground
			canJump = true;
			mInAir = false;
		}
	}
}

void Player::constrainToScreen()
{
	constrainToScreenX();
	constrainToScreenY();
}

void Player::constrainToScreenX()
{
	if (mX < 0) mX = 0;
	if (mX + mCollider.w > LEVEL_WIDTH) mX = LEVEL_WIDTH - mCollider.w;
}	 

void Player::constrainToScreenY()
{
	if (mY < 0)
	{
		mY = 0;
		mVelocity.y = 0;
	}
	if (mY + mCollider.h > LEVEL_HEIGHT)
	{
		mY = LEVEL_HEIGHT - mCollider.h;
		mVelocity.y = 0;
		canJump = true; // Allow jumping again when on the ground
	}
}

void Player::render(int camX, int camY)
{
	TextureManager& textureManager = TextureManager::getInstance();
	// Render the player texture at the adjusted position
	changeAnimation();
	if (isDashing)
	{
		int frameIndex = frame % 2;
		if (lastDirection == -1)
		{
			mTexture.renderTexture(mX - camX, mY - camY, &textureManager.getFallClips()[frameIndex], 0.0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			mTexture.renderTexture(mX - camX, mY - camY, &textureManager.getFallClips()[frameIndex]);
		}
	}
	if (mVelocity.y < 0)
	{
		int frameIndex = frame % 3;
		if (lastDirection == -1)
		{
			mTexture.renderTexture(mX - camX, mY - camY, &textureManager.getJumpClips()[frameIndex], 0.0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			mTexture.renderTexture(mX - camX, mY - camY, &textureManager.getJumpClips()[frameIndex]);
		}
	}
	else if (mVelocity.y > 0)
	{
		int frameIndex = frame % 3;
		if (lastDirection == -1)
		{
			mTexture.renderTexture(mX - camX, mY - camY, &textureManager.getJumpClips()[frameIndex], 0.0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			mTexture.renderTexture(mX - camX, mY - camY, &textureManager.getJumpClips()[frameIndex]);
		}
	}
	else if (isMoving)
	{
		int frameIndex = frame % 10;
		if (lastDirection == -1) 
		{
			mTexture.renderTexture(mX - camX, mY - camY, &textureManager.getRunClips()[frameIndex], 0.0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else 
		{
			mTexture.renderTexture(mX - camX, mY - camY, &textureManager.getRunClips()[frameIndex]);
		}
	}
	else
	{
		int frameIndex = frame % 10;
		if (lastDirection == -1)
		{
			mTexture.renderTexture(mX - camX, mY - camY, &textureManager.getIdleClips()[frameIndex], 0.0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			mTexture.renderTexture(mX - camX, mY - camY, &textureManager.getIdleClips()[frameIndex]);
		}
	}
	
}

void Player::changeAnimation()
{
	TextureManager& textureManager = TextureManager::getInstance();
	if (isDashing)
	{
		mTexture = textureManager.getDashTexture();
	}
	else if (mVelocity.y < 0)
	{
		mTexture = textureManager.getJumpTexture();
	}
	else if (mVelocity.y > 0)
	{
		mTexture = textureManager.getFallTexture();
	}
	else if (isMoving)
	{
		mTexture = textureManager.getRunTexture();
	}
	else
	{
		mTexture = textureManager.getIdleTexture();
	}
}

void Player::setVelocity(int xVel, int yVel)
{
	mVelocity = { xVel, yVel };
}

bool Player::isMaxVelocity() const
{
	return abs(mVelocity.x) == MAX_VELOCITY;
}

SDL_Point Player::getVelocity() const
{
	return mVelocity;
}

void Player::handleEvent(SDL_Event& e, int camX, int camY)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		handleKeyDown(e.key.keysym.sym, camX, camY);
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		handleKeyUp(e.key.keysym.sym);
	}
}

void Player::handleKeyDown(SDL_Keycode key, int camX, int camY)
{
	switch (key)
	{
	case SDLK_z: // Changed from SDLK_UP to SDLK_z for jump
		if (canJump)
		{
			AudioManager::getInstance().playJumpEffect();
			mVelocity.y = -JUMP_VELOCITY; // Apply jump velocity upwards
			canJump = false; // Prevent double jump
			mInAir = true; // Player is now in the air
		}
		break;
	case SDLK_LEFT:
		lastDirection = -1;
		isMoving = true;
		break;
	case SDLK_RIGHT:
		lastDirection = 1;
		isMoving = true;
		break;
	case SDLK_x:
		startDash();
		break;
	case SDLK_c: // Launch hookshot
		if (!gHookshot.isActive())
		{
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			// Adjust mouse position by subtracting the camera offset
			mouseX += camX;
			mouseY += camY;

			// Calculate direction from the player center (adjusted for the camera) to the mouse
			SDL_FPoint playerCenter = { static_cast<float>(mX) + (mCollider.w / 2.0f), static_cast<float>(mY) + (mCollider.h / 2.0f) };
			SDL_FPoint direction = { static_cast<float>(mouseX) - playerCenter.x, static_cast<float>(mouseY) - playerCenter.y };

			// Normalize the direction
			float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			direction.x /= magnitude;
			direction.y /= magnitude;

			// Launch the hookshot from the center of the player
			gHookshot.launch(direction, HOOKSHOT_VELOCITY, playerCenter);
		}
		break;
	}
}

void Player::handleKeyUp(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_LEFT:
		if (lastDirection == -1)
		{
			mVelocity.x = 0;
			isMoving = false;
		}
		break;
	case SDLK_RIGHT:
		if (lastDirection == 1)
		{
			mVelocity.x = 0;
			isMoving = false;
		}
		break;
	}
}

void Player::debug_stuff()
{
	std::cout << "x-velocity: " << mVelocity.x << "\n";
	std::cout << "y-coord: " << mY << "\n";
}