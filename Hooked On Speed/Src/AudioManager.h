#pragma once

#include <SDL_mixer.h>
#include <stdio.h>

// Singleton class responsible for managing game audio.
// The AudioManager handles loading, playing, and cleaning up
// game music and sound effects.
class AudioManager {
public:
    // Retrieves the singleton instance of AudioManager.
    // @return A reference to the singleton instance.
    static AudioManager& getInstance();

    // Loads music tracks for the game.
    // @return True if all music is successfully loaded, false otherwise.
    bool loadMusic();

    // Loads sound effects for the game.
    // @return True if all sound effects are successfully loaded, false otherwise.
    bool loadSoundEffects();

    // Plays the menu music in a loop.
    void playMenuMusic();

    // Plays the game music in a loop.
    void playGameMusic();

    // Plays the dash sound effect once.
    void playDashEffect();

    // Plays the jump sound effect once.
    void playJumpEffect();

    // Frees all audio resources.
    void closeAudio();

private:
    // Constructor and Destructor
    AudioManager();
    ~AudioManager();

    // Copy constructor and assignment operator are disabled
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    // Audio resources (stored as private members)
    Mix_Music* gMenuMusic; // Pointer to the menu music.
    Mix_Music* gGameMusic; // Pointer to the game music.
    Mix_Chunk* gDashEffect; // Pointer to the dash sound effect.
    Mix_Chunk* gJumpEffect; // Pointer to the jump sound effect.
};