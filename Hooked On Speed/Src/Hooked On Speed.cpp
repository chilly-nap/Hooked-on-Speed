// Hooked On Speed.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "MediaLoader.h"
#include "Menu.h"
#include "Player.h"
#include "RenderGame.h"
#include "TextureLoader.h"
#include "Tile.h"
#include "WindowManager.h"
#include <SDL_mixer.h>


int main(int argc, char* args[])
{
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Quit flag
            bool quit = false;
            bool loadFlag = false;

            SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
            SDL_Event e;

            Player gPlayer = Player(0, 0);

            AudioManager& audioManager = AudioManager::getInstance();

            while (!quit)
            {   
                if (!loadFlag)
                {
                    if (Mix_PlayingMusic() == 0)
                    {
                        //Play the music
						audioManager.playMenuMusic();
                    
                    }
					startMenu(e, quit, loadFlag);
                }
                else 
                {
                    if (Mix_PlayingMusic() == 0)
                    {
                        //Play the music
						audioManager.playGameMusic();
                    }
                    gPlayer.mLevelComplete = false;
                    renderGame(gPlayer, e, quit, camera, loadFlag);
                }
            }
        }
    }

    return 0;
}