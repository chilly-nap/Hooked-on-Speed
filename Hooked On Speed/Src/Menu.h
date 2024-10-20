#pragma once

#include "Player.h"
#include "TextureLoader.h"
#include <SDL.h>
#include <string>

#include <vector>

// Starts the menu
void startMenu(SDL_Event& e, bool& quit, bool& loadFlag);