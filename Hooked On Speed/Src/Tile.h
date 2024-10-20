#pragma once

#include "GameObject.h"
#include "TextureLoader.h"
#include "WindowManager.h"
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <vector>

class Tile : public GameObject
{
public:
    // Constructor to initialize the tile's position, type, and other attributes
    Tile(int x, int y, int tileType);

    // Render the tile based on its position and the camera view
    void render(SDL_Rect& camera);

    // Get the type of the tile
    int getType() const;

    // Get the collision box of the tile
    SDL_Rect getBox() const;

    // Attributes of the tile, including its position and size
    SDL_Rect mBox;  // The bounding box of the tile

    // Type of the tile, which could represent different textures or behaviors
    int mType;      // The specific type of the tile
};

// Function to check for collision between a camera and another object
bool checkCollision(SDL_Rect& camera, SDL_Rect& other);

// Function to determine if a tile touches a wall
bool touchesWall(SDL_Rect box, const std::vector<Tile*>& tiles);

// Function to set up the tiles (implementation not shown in this header)
bool setTiles();

// External variables for tile management
extern std::vector<Tile*> tileSet; // Collection of all tiles in the level

// External variables for level management
extern int totalTiles;     // Total number of tiles in the level
extern int levelSelector;  // Current level being played
extern int TILE_HEIGHT;    // Height of a tile
extern int TILE_WIDTH;     // Width of a tile