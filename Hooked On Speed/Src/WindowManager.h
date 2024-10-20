#pragma once

#include "MediaLoader.h"
#include "Player.h"
#include "TextureLoader.h"
#include "Tile.h"
#include <vector>

class Window
{
public:
    // Initializes internal variables for the window
    Window();

    // Creates the window and returns success status
    bool initWindow();

    // Creates and returns a renderer associated with the internal window
    SDL_Renderer* createRenderer();

    // Deallocates internal resources used by the window
    void freeWindow();

    // Returns the width of the window
    int getWidth();

    // Returns the height of the window
    int getHeight();

private:
    // Pointer to the SDL_Window instance
    SDL_Window* mWindow;

    // Window dimensions
    int mWidth;  // Width of the window
    int mHeight; // Height of the window
};

// Current window instance
extern Window gWindow;

// General SDL renderer
extern SDL_Renderer* gRenderer;

// Screen dimensions for rendering
extern const int SCREEN_WIDTH;  // Width of the screen
extern const int SCREEN_HEIGHT; // Height of the screen
extern int LEVEL_WIDTH;   // Width of the level
extern int LEVEL_HEIGHT;  // Height of the level