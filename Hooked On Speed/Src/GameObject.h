#pragma once
#include "TextureLoader.h"

// Represents a generic game object that can be rendered and interacted with
class GameObject
{
public:
    // Default constructor
    GameObject() = default;

    // Parameterized constructor to initialize rigidity and hitbox status
    GameObject(bool isRigid, bool hasHitbox);

    // Virtual destructor for proper cleanup in derived classes
    virtual ~GameObject() = default;

    // Get the object's hitbox for collision detection
    virtual SDL_Rect getHitbox() const;

    // Check for collision with another object based on their hitboxes
    virtual bool checkCollision(SDL_Rect& camera, SDL_Rect& other) const;

    // Set the position of the object on the screen
    void setPosition(int x, int y);

    // Check if the object is rigid (i.e., static or immovable)
    bool isRigid() const;

    // Check if the object has a hitbox for collision detection
    bool hasHitbox() const;

    // Object's position on the X-axis
    int mX;

    // Object's position on the Y-axis
    int mY;

    // Whether the object is rigid (immovable)
    bool mIsRigid;

    // Whether the object has a hitbox for collision detection
    bool mHasHitbox;

    // Texture used for rendering the game object
    gTexture mTexture;

    // Object's hitbox / collider for collision detection
    SDL_Rect mCollider;
};