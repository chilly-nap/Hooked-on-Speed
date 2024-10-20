#pragma once

#include "Menu.h"

void startMenu(SDL_Event& e, bool& quit, bool& loadFlag)
{
	SDL_Rect menuClip = { 0, 0, 800, 600 };
	SDL_Rect ButtonClip = { 0, 0, 200, 50 };
	TextureManager& textureManager = TextureManager::getInstance();
    while (SDL_PollEvent(&e) != 0)
    {
        // User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }

		// Check for mouse events
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			// Get the mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);

			// Check if the mouse is within the button's rectangle
			if (x >= 225 && x <= 225 + ButtonClip.w &&
				y >= 305 && y <= 305 + ButtonClip.h)
			{
				loadFlag = true;
				Mix_HaltMusic();
			}
		}
    }

    SDL_SetRenderDrawColor(gRenderer, 92, 159, 247, 0xFF);
    SDL_RenderClear(gRenderer);

	textureManager.getBGTexture().renderTexture(0, 0, &menuClip);
	textureManager.getLogoTexture().renderTexture(125, 50);
	textureManager.getButtonOneTexture().renderTextureCopy(225, 305, &textureManager.getClipUI(), &ButtonClip);
	textureManager.getMenuTextTexture().renderTexture(275, 318);
    SDL_RenderPresent(gRenderer);
}