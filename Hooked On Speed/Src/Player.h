#pragma once

#include "GameObject.h"
#include "Hookshot.h"
#include "MediaLoader.h"
#include "TextureLoader.h"
#include "Tile.h"
#include "WindowManager.h"
#include <cmath>
#include <iostream>
#include <vector>

// Player class definition
class Player : public GameObject
{
public:
	// Constructor and Destructor

	Player() = default; // Default constructor
	Player(int x, int y); // Parameterized constructor
	~Player(); // Destructor

	// Level
	bool mLevelComplete; // Whether the level is complete

	// Public Methods
	void update(); // Override update function to handle player-specific logic
	void render(int camX, int camY); // Override render function to draw the player
	void handleEvent(SDL_Event& e, int camX, int camY); // Handle input events
	void setVelocity(int xVel, int yVel); // Set the player's velocity
	bool isMaxVelocity() const; // Check if the player has reached max velocity
	bool getEndLevel(); // Get the end level object
	SDL_Point getVelocity() const; // Get the player's velocity

private:
	// Player State

	// Air movement
	bool mInAir; // Whether the player is in the air
	bool isMoving; // Whether the player is moving

	// Directional State
	int lastDirection; // The last direction the player was moving
	bool canJump; // Whether the player can jump

	int stamina; // Current stamina
	bool isSprinting; // Sprinting state

	// Dashing movement
	bool isDashing; // Whether the player is dashing
	int dashTime; // Time remaining for the dash
	int dashCooldown; // Cooldown time before the next dash

	// Player Velocity
	SDL_Point mVelocity; // Player's velocity (x and y)

	// Dash Methods
	void updateDash(); // Update dash state
	void endDash(); // End the current dash

	// Movement Methods
	void updateMovement();// Update player movement
	void accelerate(); // Accelerate the player
	void applyGravity(); // Apply gravity to the player

	// Constrainy
	void constrainToScreen(); // Constrain player to screen boundaries
	void constrainToScreenX(); // Constrain X position to screen
	void constrainToScreenY(); // Constrain Y position to screen

	// Input Handling Methods
	void handleKeyDown(SDL_Keycode key, int camX, int camY); // Handle key down events
	void handleKeyUp(SDL_Keycode key); // Handle key up events
	void startDash(); // Start dashing

	void changeAnimation();

	// Utility Methods
	void debug_stuff(); // Debugging utility
};