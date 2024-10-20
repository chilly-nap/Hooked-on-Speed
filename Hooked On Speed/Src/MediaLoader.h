#pragma once

#include "AudioManager.h"
#include "Player.h"
#include "TextureLoader.h"
#include "TextureManager.h"
#include "Tile.h"
#include "WindowManager.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Initializes everything needed in the game
bool init();

// Loading media in general (e.g textures)
bool loadMedia();

// Freeing memories and quiting subsystems
void close();