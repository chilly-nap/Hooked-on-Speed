#pragma once

#include "RenderGame.h"

void handleCamera(SDL_Rect& camera, const Player& player)
{
    // Center the camera on the player
    camera.x = (player.mX + player.mCollider.w / 2) - SCREEN_WIDTH / 2;
    camera.y = (player.mY + player.mCollider.h / 2) - SCREEN_HEIGHT / 2;

    // Keep the camera within the level boundaries
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH - camera.w)
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h)
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

void renderGame(Player& gPlayer, SDL_Event& e, bool& quit, SDL_Rect& camera, bool& loadFlag)
{
	TextureManager& textureManager = TextureManager::getInstance();
    while (SDL_PollEvent(&e) != 0)
    {
        // User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }

        gPlayer.handleEvent(e, camera.x, camera.y);
    }

    // update player
    handleCamera(camera, gPlayer);
    gPlayer.update();

	gHookshot.update(gPlayer);

    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(gRenderer);

    for (int i = 11; i > 0; --i)
    {
        // Invert the parallax factor, so layers with lower i (farther) move slower, and layers with higher i (closer) move faster
        float parallaxFactor = 1.0f - (i / 10); // Adjust denominator for fine-tuning

        // Calculate offset for the layer based on the camera position and parallax factor
        int offsetX = static_cast<int>(-camera.x * parallaxFactor);
        int offsetY = static_cast<int>(-camera.y * parallaxFactor);

        // Get the width and height of the texture
        int textureWidth = textureManager.getLayersTexture()[i].getWidth();
        int textureHeight = textureManager.getLayersTexture()[i].getHeight();;

        // Render the layer multiple times to ensure full coverage of the screen
        for (int x = offsetX; x < SCREEN_WIDTH; x += textureWidth)
        {
            for (int y = offsetY; y < SCREEN_HEIGHT; y += textureHeight)
            {
                textureManager.getLayersTexture()[i].renderTexture(x, y, nullptr);
            }
        }
    }

    // Render all tiles
    for (int i = 0; i < tileSet.size(); ++i)
    {
        tileSet[i]->render(camera);
    }

    // Render player with camera offsets
    textureManager.getTileTexture().renderTexture(660 - 32 - camera.x, 314 - 32 - camera.y, &textureManager.getEndLevelClip());
    gPlayer.render(camera.x, camera.y);
    gHookshot.render(camera.x, camera.y);

    // Present the renderer
    SDL_RenderPresent(gRenderer);

	if (gPlayer.getEndLevel())
	{
		loadFlag = false;
        Mix_HaltMusic();
	}
}