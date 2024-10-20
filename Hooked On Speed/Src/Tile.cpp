#pragma once
#include "Tile.h"

// Global Variables
int totalTiles = 0;
int TILE_HEIGHT = 32;
int TILE_WIDTH = 32;
int levelSelector = 1;
std::vector<Tile*> tileSet; // Use a vector of Tile pointers

enum TileType
{
    TILE_EMPTY = 0,   // Represents an empty tile
    TILE_GROUND = 1,  // Represents a ground tile
    TILE_WATER = 2,   // Represents a water tile
    TILE_LAVA = 3,    // Represents a lava tile
    TILE_SPIKE = 4    // Represents a spike tile
};

// Tile Class Definitions
Tile::Tile(int x, int y, int tileType)
{
    // Get the offsets
    mBox.x = x;
    mBox.y = y;

    // Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    // Get the tile type
    mType = tileType;
}

void Tile::render(SDL_Rect& camera)
{
    // If the tile is on screen
	TextureManager& textureManager = TextureManager::getInstance();
    if (checkCollision(camera, mBox))
    {
        textureManager.getTileTexture().renderTexture(mBox.x - camera.x, mBox.y - camera.y, &textureManager.getTileClips()[mType]);
    }
}

int Tile::getType() const
{
    return mType;
}

// Return a const reference to avoid copying
SDL_Rect Tile::getBox() const
{
    return mBox;
}

bool setTiles()
{
    bool tilesLoaded = true;

    int x = 0, y = 0;
    std::string fileName = "Assets/Maps/Level" + std::to_string(levelSelector) + ".map";
    std::ifstream map(fileName);

	TextureManager& textureManager = TextureManager::getInstance();

    if (map.fail())
    {
        std::cerr << "Unable to load map file!\n";
        tilesLoaded = false;
    }
    else
    {
        int numColumns;
        int numRows;

        // Read number of columns (length of the level)
        map >> numColumns;
        LEVEL_WIDTH = numColumns * TILE_WIDTH; // Adjust LEVEL_WIDTH based on the number of columns

        // Read number of tiles
        map >> numRows;
        totalTiles = numRows * numColumns;
        tileSet.clear(); // Clear any previously loaded tiles

        std::cout << "Expected total tiles: " << totalTiles << "\n";
        std::cout << "Reading tile data...\n";

        for (int i = 0; i < totalTiles; ++i)
        {
            // Determines what kind of tile will be made
            int tileType = -1;

            // Read tile from map file
            map >> tileType;
            
            // If there was a problem reading the map
            if (map.fail())
            {
                std::cerr << "Error loading map: Unexpected end of file at tile " << i << "!\n";
                tilesLoaded = false;
                break;
            }

            // If the number is a valid tile number
            if (tileType > 0) // Allow TILE_EMPTY (0) as a valid tile type
            {
                tileSet.push_back(new Tile(x, y, tileType)); // Add the new tile to the vector
            }
            else if (tileType < 0)
            {
                // Stop loading map
                std::cerr << "Error loading map: Invalid tile type at " << i << "!\n";
                tilesLoaded = false;
                break;
            }

            x += TILE_WIDTH;

            // If we've gone too far in the x direction
            if (x >= LEVEL_WIDTH)
            {
                // Move back to the start of the row
                x = 0;

                // Move to the next row
                y += TILE_HEIGHT;
            }
        }

        if (tilesLoaded)
        {
			// Set tile clips
			textureManager.getTileClips()[TILE_GROUND].x = 384;
			textureManager.getTileClips()[TILE_GROUND].y = 368;
			textureManager.getTileClips()[TILE_GROUND].w = TILE_WIDTH;
			textureManager.getTileClips()[TILE_GROUND].h = TILE_HEIGHT;
        }
    }

    std::cout << "Finished Reading...\n";
    map.close();
    return tilesLoaded;
}

// Accept const references to allow temporary objects
bool checkCollision(const SDL_Rect& camera, const SDL_Rect& other)
{
    return SDL_HasIntersection(&camera, &other);
}

bool touchesWall(SDL_Rect box, const std::vector<Tile*>& tiles) // Use vector in the parameter
{
    // Go through the tiles
    for (int i = 0; i < tileSet.size(); ++i)
    {
        // If the collision box touches the wall tile
        if (checkCollision(box, tiles[i]->getBox())) // Corrected parenthesis and const correctness
        {
            return true;
        }
    }
    return false;
}
