#include "TextureManager.h"
#include "Tile.h"

TextureManager::TextureManager()
	:gFont(nullptr) { // Initialize gFont to nullptr
}

TextureManager::~TextureManager() {
	freeAllTextures(); // Free all loaded textures when the TextureManager is destroyed
}

// Load a texture from a specified file path
void TextureManager::loadTexture(gTexture& texture, const std::string& path) {
	if (!texture.loadFromFile(path)) { // Attempt to load the texture
		printf("Failed to load texture!\n"); // Print an error message if loading fails
	}
}

// Load all player-related textures
void TextureManager::loadPlayerTextures() {
	loadTexture(gIdleTexture, "Assets/Textures/Player/_Idle.png"); // Load idle texture
	loadTexture(gRunTexture, "Assets/Textures/Player/_Run.png"); // Load running texture
	loadTexture(gJumpTexture, "Assets/Textures/Player/_Jump.png"); // Load jumping texture
	loadTexture(gFallTexture, "Assets/Textures/Player/_Fall.png"); // Load falling texture
	loadTexture(gDashTexture, "Assets/Textures/Player/_Dash.png"); // Load dashing texture
}

void TextureManager::setPlayerClips()
{
	// Set Idle Animation Clips
	for (int i = 0; i < 10; i++)
	{
		gIdleClip[i].x = i * 120 + 44;
		gIdleClip[i].y = 43;
		gIdleClip[i].w = 21;
		gIdleClip[i].h = 38;
	}

	// Set Run Animation Clips
	{
		gRunClip[0].x = 43;
		gRunClip[0].y = 42;
		gRunClip[0].w = 27;
		gRunClip[0].h = 37;

		gRunClip[1].x = 165;
		gRunClip[1].y = 44;
		gRunClip[1].w = 24;
		gRunClip[1].h = 37;

		gRunClip[2].x = 289;
		gRunClip[2].y = 43;
		gRunClip[2].w = 24;
		gRunClip[2].h = 37;

		gRunClip[3].x = 407;
		gRunClip[3].y = 43;
		gRunClip[3].w = 24;
		gRunClip[3].h = 37;

		gRunClip[4].x = 524;
		gRunClip[4].y = 43;
		gRunClip[4].w = 24;
		gRunClip[4].h = 37;

		gRunClip[5].x = 641;
		gRunClip[5].y = 43;
		gRunClip[5].w = 28;
		gRunClip[5].h = 37;

		gRunClip[6].x = 764;
		gRunClip[6].y = 43;
		gRunClip[6].w = 24;
		gRunClip[6].h = 37;

		gRunClip[7].x = 887;
		gRunClip[7].y = 43;
		gRunClip[7].w = 24;
		gRunClip[7].h = 37;

		gRunClip[8].x = 1007;
		gRunClip[8].y = 43;
		gRunClip[8].w = 24;
		gRunClip[8].h = 37;

		gRunClip[9].x = 1122;
		gRunClip[9].y = 43;
		gRunClip[9].w = 28;
		gRunClip[9].h = 37;
	}

	// Set Jump Animation Clips
	{
		gJumpClip[0].x = 44;
		gJumpClip[0].y = 43;
		gJumpClip[0].w = 27;
		gJumpClip[0].h = 37;

		gJumpClip[1].x = 165;
		gJumpClip[1].y = 43;
		gJumpClip[1].w = 24;
		gJumpClip[1].h = 37;

		gJumpClip[2].x = 285;
		gJumpClip[2].y = 43;
		gJumpClip[2].w = 24;
		gJumpClip[2].h = 37;
	}

	// Set Fall Animation Clips
	{
		gFallClip[0].x = 40;
		gFallClip[0].y = 43;
		gFallClip[0].w = 27;
		gFallClip[0].h = 37;

		gFallClip[1].x = 160;
		gFallClip[1].y = 43;
		gFallClip[1].w = 27;
		gFallClip[1].h = 37;

		gFallClip[2].x = 280;
		gFallClip[2].y = 43;
		gFallClip[2].w = 27;
		gFallClip[2].h = 37;
	}

	// Set Dash Animation Clips
	{
		gDashClip[0].x = 41;
		gDashClip[0].y = 46;
		gDashClip[0].w = 32;
		gDashClip[0].h = 33;

		gDashClip[1].x = 161;
		gDashClip[1].y = 46;
		gDashClip[1].w = 32;
		gDashClip[1].h = 33;
	}
}

// Load background textures for the game
void TextureManager::loadBackgroundTextures() {
	for (int i = 0; i < 12; i++) { // Loop through layers
		std::string layerFile = "Assets/Textures/Background/Layer_" + std::to_string(i + 1) + ".png"; // Construct file path
		gLayersTexture[i].loadFromFile(layerFile); // Load each layer texture
	}
	loadTexture(gBGTexture, "Assets/Textures/Background/Menu.png"); // Load background texture for menu
}

// Load UI textures for the game's menu
void TextureManager::loadMenuTextures() {
	loadTexture(gLogoTexture, "Assets/Textures/UI/Logo.png"); // Load logo texture
	loadTexture(gButtonOneTexture, "Assets/Textures/UI/Spritesheet_UI.png"); // Load button texture

	// Load font for rendering text
	gFont = TTF_OpenFont("Assets/Font/MinimalPixelFont.ttf", 26);
	if (gFont == NULL) { // Check if the font was loaded successfully
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError()); // Print error if loading failed
	}
	else {
		SDL_Color textColor = { 0, 0, 0 }; // Set text color to black
		if (!gMenuTextTexture.loadFromRenderedText("START GAME", textColor)) { // Render "START GAME" text
			printf("Failed to render text texture!\n"); // Print error if rendering failed
		}
	}
}

// Set UI clips for the menu
void TextureManager::setMenuClips() {
	gClipUI = { 288, 198, 64, 24 }; // Set the UI clip rectangle
	gEndLevelBox = { 660 - 32, 314 - 32, 48, 64 }; // Set end level box rectangle
}

// Load tile textures for the game
void TextureManager::loadTileTextures() {
	loadTexture(gTileTexture, "Assets/Textures/Tileset/tileset.png"); // Load tile texture
	if (!setTiles()) { // Check if tiles are set successfully
		printf("Failed to load tile set!\n"); // Print error if loading failed
	}
	gEndLevelClip = { 960, 16, 48, 64 }; // Set end level clip rectangle
}

// Load all textures needed for the game
void TextureManager::loadAllTextures() {
	loadPlayerTextures(); // Load player textures
	setPlayerClips(); // Set player animation clips

	loadBackgroundTextures(); // Load background textures
	loadMenuTextures(); // Load menu textures

	setMenuClips(); // Set UI clips for menu
	loadTileTextures(); // Load tile textures
}

// Free all loaded textures to avoid memory leaks
void TextureManager::freeAllTextures() {
	for (int i = 0; i < 12; i++) {
		gLayersTexture[i].freeTexture(); // Free each layer texture
	}

	gMenuTextTexture.freeTexture(); // Free menu text texture
	TTF_CloseFont(gFont); // Close the font
	gFont = NULL; // Set font pointer to nullptr

	// Free player textures
	gIdleTexture.freeTexture();
	gRunTexture.freeTexture();
	gJumpTexture.freeTexture();
	gFallTexture.freeTexture();
	gDashTexture.freeTexture();
	gLogoTexture.freeTexture();
	gButtonOneTexture.freeTexture();
}