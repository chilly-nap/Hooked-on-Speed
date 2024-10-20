#pragma once
#include "GameObject.h"
#include "Player.h"  // Include the Player class definition
#include "Tile.h"
#include "WindowManager.h"
#include <cmath>
#include <SDL.h>

extern const float HOOKSHOT_VELOCITY;
class Player;

class Hookshot : public GameObject
{
public:
    // Constructor: Initializes the hookshot with a given starting position
    Hookshot();

    // Destructor
    ~Hookshot() = default;

    // Launch the hookshot with a given velocity and direction
    void launch(const SDL_FPoint& direction, float velocity, const SDL_FPoint& startPosition);

    // Update hookshot position based on its velocity and direction
    void update(Player& gPlayer);

    // Check if the hookshot has hit a target (tile, object, etc.)
    bool checkHit();

    // Stop the hookshot (called when the hookshot is released or hits a target)
    void stop();

    // Render the hookshot on screen
    void render(int camX, int camY);

    // Get the current velocity of the hookshot
    SDL_FPoint getVelocity() const;

    // Get the direction of the hookshot
    SDL_FPoint getDirection() const;

    // Check if the hookshot is active (launched)
    bool isActive() const;

private:
    float gX;
    float gY;

    // Hookshot's velocity
    SDL_FPoint mVelocity;

    // Direction the hookshot is moving (normalized vector)
    SDL_FPoint mDirection;

    // Whether the hookshot is active
    bool mActive;

    // Hitbox for the hookshot
    SDL_Rect mHitbox;
};

extern Hookshot gHookshot;
