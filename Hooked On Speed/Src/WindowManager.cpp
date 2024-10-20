#pragma once
#include "TextureLoader.h"
#include "WindowManager.h"

// Global renderer pointer
SDL_Renderer* gRenderer = nullptr;

// Current window instance
Window gWindow;

// Screen dimensions
const int SCREEN_WIDTH = 640;  // Width of the screen
const int SCREEN_HEIGHT = 480; // Height of the screen

// Level dimensions
int LEVEL_WIDTH = 1200;  // Width of the level
int LEVEL_HEIGHT = 800;   // Height of the level

// Constructor
Window::Window()
{
    mWindow = NULL;  // Initialize window pointer to null
    mWidth = 0;      // Initialize width to 0
    mHeight = 0;     // Initialize height to 0
}

// Initializes the window
bool Window::initWindow()
{
    // Create a window with specified title and dimensions
    mWindow = SDL_CreateWindow("Hooked on Speed", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Check if the window was created successfully
    if (mWindow != NULL)
    {
        mWidth = SCREEN_WIDTH;   // Set window width
        mHeight = SCREEN_HEIGHT;  // Set window height
    }

    return mWindow != NULL;  // Return success status
}

// Creates and returns a renderer associated with the internal window
SDL_Renderer* Window::createRenderer()
{
    // Create an accelerated renderer with vsync enabled
    return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

// Deallocates resources associated with the window
void Window::freeWindow()
{
    // Check if the window exists before attempting to destroy it
    if (mWindow != NULL)
    {
        SDL_DestroyWindow(mWindow);  // Destroy the window
    }

    mWidth = 0;  // Reset width
    mHeight = 0; // Reset height
}

// Returns the width of the window
int Window::getWidth()
{
    return mWidth;  // Return current window width
}

// Returns the height of the window
int Window::getHeight()
{
    return mHeight; // Return current window height
}