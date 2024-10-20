#pragma once

#include "TextureLoader.h"
#include "WindowManager.h"

// Constructor for gTexture class
gTexture::gTexture()
{
    mTexture = NULL; // Initialize texture to null
    mWidth = 0;      // Initialize width to zero
    mHeight = 0;     // Initialize height to zero
}

// Destructor for gTexture class
gTexture::~gTexture()
{
    freeTexture(); // Free texture resources when the object is destroyed
}

// Frees the texture and resets its properties
void gTexture::freeTexture()
{
    SDL_DestroyTexture(mTexture); // Destroy the current texture if it exists
    mTexture = NULL;               // Reset texture pointer to null
    mWidth = 0;                    // Reset width to zero
    mHeight = 0;                   // Reset height to zero
}

// Loads a texture from a file
bool gTexture::loadFromFile(std::string path)
{
    // Free any existing texture to avoid memory leaks
    freeTexture();

    SDL_Texture* newTexture = NULL; // Pointer to hold the new texture
    SDL_Surface* loadedSurface = IMG_Load(path.c_str()); // Load image into surface

    // Check if the image was loaded successfully
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Set color key (transparency) for the loaded surface
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // Create a texture from the loaded surface
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // Get the dimensions of the loaded texture
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Free the old surface as it is no longer needed
        SDL_FreeSurface(loadedSurface);
    }

    // Assign the newly created texture to the member variable
    mTexture = newTexture;
    return mTexture != NULL; // Return success status
}

// Loads a texture from rendered text
bool gTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    TextureManager& textureManager = TextureManager::getInstance(); // Get the texture manager instance
    freeTexture(); // Free any existing texture

    // Render text surface from the specified text and color
    SDL_Surface* textSurface = TTF_RenderText_Solid(textureManager.getFont(), textureText.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // Create texture from the rendered text surface
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get the dimensions of the rendered text texture
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        // Free the text surface as it is no longer needed
        SDL_FreeSurface(textSurface);
    }

    // Return success status
    return mTexture != NULL;
}

// Renders the texture at the specified coordinates with optional parameters
void gTexture::renderTexture(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    // Set the rectangle for rendering at the specified position
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    // If a clipping rectangle is provided, use it
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render the texture with optional rotation, center, and flipping
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

// Renders a texture using a specified destination rectangle
void gTexture::renderTextureCopy(int x, int y, SDL_Rect* clip, SDL_Rect* dest)
{
    // Set the destination rectangle for rendering
    SDL_Rect renderQuad = { x, y, clip->w, clip->h };

    // If a destination rectangle is provided, use its dimensions
    if (dest != nullptr)
    {
        renderQuad.w = dest->w;
        renderQuad.h = dest->h;
    }

    // Render the texture to the screen
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

// Returns the width of the texture
int gTexture::getWidth()
{
    return mWidth; // Return the stored width of the texture
}

// Returns the height of the texture
int gTexture::getHeight()
{
    return mHeight; // Return the stored height of the texture
}
