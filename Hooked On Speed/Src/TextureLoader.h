#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>


class gTexture
{
public:
    // Default constructor
    gTexture();

    // Destructor
    ~gTexture();

    // Seperate function to free texture
    void freeTexture();

    // Load image from a specified file path
    bool loadFromFile(std::string path);

    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

    // Render the texture at the specified position
    void renderTexture(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void renderTextureCopy(int x, int y, SDL_Rect* clip = nullptr, SDL_Rect* dest = nullptr);

    // Get texture width
    int getWidth();

    // Get texture height
    int getHeight();

private:
    // The actual hardware texture
    SDL_Texture* mTexture;

    // Texture dimensions
    int mWidth;
    int mHeight;
};
