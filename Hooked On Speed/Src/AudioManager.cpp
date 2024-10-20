#pragma once

#include "AudioManager.h"

// Singleton instance method
AudioManager& AudioManager::getInstance() {
    static AudioManager instance; // Create a static instance of AudioManager
    return instance; // Return the singleton instance
}

// Constructor (initializes pointers to null)
AudioManager::AudioManager()
    : gMenuMusic(nullptr), gGameMusic(nullptr), gDashEffect(nullptr), gJumpEffect(nullptr) {
    // Initialize audio resource pointers to nullptr
}

// Destructor (calls closeAudio to free resources)
AudioManager::~AudioManager() {
    closeAudio(); // Clean up resources when AudioManager is destroyed
}

bool AudioManager::loadMusic() {
    // Load the menu music
    gMenuMusic = Mix_LoadMUS("Assets/Music/Menu_Music.mp3");
    if (gMenuMusic == nullptr) {
        printf("Failed to load Menu music! SDL_mixer Error: %s\n", Mix_GetError());
        return false; // Return false if loading fails
    }

    // Load the game music
    gGameMusic = Mix_LoadMUS("Assets/Music/Game_Music.mp3");
    if (gGameMusic == nullptr) {
        printf("Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError());
        return false; // Return false if loading fails
    }

    return true; // Return true if both music tracks are successfully loaded
}

bool AudioManager::loadSoundEffects() {
    // Load the dash sound effect
    gDashEffect = Mix_LoadWAV("Assets/Sound_Effect/dash_effect.wav");
    if (gDashEffect == nullptr) {
        printf("Failed to load dash sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false; // Return false if loading fails
    }

    // Load the jump sound effect
    gJumpEffect = Mix_LoadWAV("Assets/Sound_Effect/jump_effect.mp3");
    if (gJumpEffect == nullptr) {
        printf("Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    return true; // Return true if sound effects are loaded successfully
}

void AudioManager::playMenuMusic() {
    if (gMenuMusic != nullptr) {
        Mix_PlayMusic(gMenuMusic, -1); // Loop the menu music indefinitely
    }
}

void AudioManager::playGameMusic() {
    if (gGameMusic != nullptr) {
        Mix_PlayMusic(gGameMusic, -1); // Loop the game music indefinitely
    }
}

void AudioManager::playDashEffect() {
    if (gDashEffect != nullptr) {
        Mix_PlayChannel(-1, gDashEffect, 0); // Play the dash sound effect once
    }
}

void AudioManager::playJumpEffect() {
    if (gJumpEffect != nullptr) {
        Mix_PlayChannel(-1, gJumpEffect, 0); // Play the jump sound effect once
    }
}

void AudioManager::closeAudio() {
    // Free the menu music if it was loaded
    if (gMenuMusic != nullptr) {
        Mix_FreeMusic(gMenuMusic);
        gMenuMusic = nullptr; // Set pointer to nullptr after freeing
    }

    // Free the game music if it was loaded
    if (gGameMusic != nullptr) {
        Mix_FreeMusic(gGameMusic);
        gGameMusic = nullptr; // Set pointer to nullptr after freeing
    }

    // Free the dash sound effect if it was loaded
    if (gDashEffect != nullptr) {
        Mix_FreeChunk(gDashEffect);
        gDashEffect = nullptr; // Set pointer to nullptr after freeing
    }

    // Free the jump sound effect if it was loaded
    if (gJumpEffect != nullptr) {
        Mix_FreeChunk(gJumpEffect);
        gJumpEffect = nullptr; // Set pointer to nullptr after freeing
    }
}