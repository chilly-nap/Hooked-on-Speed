#pragma once

#include "TextureLoader.h"
#include <array>
#include <memory>
#include <SDL_ttf.h>
#include <string>

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance; // Guaranteed to be destroyed
        return instance; // Return reference to the instance
    }

    // Delete copy constructor and assignment operator
    TextureManager(TextureManager const&) = delete;
    void operator=(TextureManager const&) = delete;

    void loadTexture(gTexture& texture, const std::string& path);
    void loadPlayerTextures();
    void setPlayerClips();
    void loadBackgroundTextures();
    void loadMenuTextures();
    void setMenuClips();
    void loadTileTextures();
    void loadAllTextures();
    void freeAllTextures();

    // Getters for textures and clips
    gTexture& getMenuTextTexture() { return gMenuTextTexture; }
    gTexture& getLogoTexture() { return gLogoTexture; }
    gTexture& getButtonOneTexture() { return gButtonOneTexture; }
    gTexture& getBGTexture() { return gBGTexture; }
    gTexture& getTileTexture() { return gTileTexture; }
    SDL_Rect* getTileClips() { return gTileClips; }
    SDL_Rect& getClipUI() { return gClipUI; }
    gTexture * getLayersTexture() { return gLayersTexture; }
	TTF_Font* getFont() { return gFont; }

    // Player Animation getters
    gTexture& getIdleTexture() { return gIdleTexture; }
    SDL_Rect* getIdleClips() { return gIdleClip; }
    gTexture& getRunTexture() { return gRunTexture; }
    SDL_Rect* getRunClips() { return gRunClip; }
    gTexture& getJumpTexture() { return gJumpTexture; }
    SDL_Rect* getJumpClips() { return gJumpClip; }
    gTexture& getFallTexture() { return gFallTexture; }
    SDL_Rect* getFallClips() { return gFallClip; }
    gTexture& getDashTexture() { return gDashTexture; }
    SDL_Rect* getDashClips() { return gDashClip; }
    SDL_Rect& getEndLevelClip() { return gEndLevelClip; }
    SDL_Rect& getEndLevelBox() { return gEndLevelBox; }

private:
    TextureManager(); // Constructor is private to prevent instantiation
    ~TextureManager(); // Destructor

	// Menu Textures
    gTexture gMenuTextTexture;
    gTexture gLogoTexture;
    gTexture gButtonOneTexture;
    gTexture gBGTexture;
    SDL_Rect gClipUI;

	// Background Textures
    gTexture gLayersTexture[12];

    // Tile textures
    SDL_Rect gTileClips[5];
    gTexture gTileTexture;

    // Player Animation
    gTexture gIdleTexture;
    SDL_Rect gIdleClip[10];

    gTexture gRunTexture;
    SDL_Rect gRunClip[10];

    gTexture gJumpTexture;
    SDL_Rect gJumpClip[3];

    gTexture gFallTexture;
    SDL_Rect gFallClip[3];

    gTexture gDashTexture;
    SDL_Rect gDashClip[2];

    SDL_Rect gEndLevelClip;
    SDL_Rect gEndLevelBox;
    TTF_Font* gFont;
};
