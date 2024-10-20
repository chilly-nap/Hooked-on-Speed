#pragma once

#include "Player.h"
#include "TextureLoader.h" // Include necessary headers
#include "Tile.h"
#include <SDL.h>

void handleCamera(SDL_Rect& camera, const Player& player);

// Declare the renderGame function
void renderGame(Player& gPlayer, SDL_Event& e, bool& quit, SDL_Rect& camera, bool& loadFlag);