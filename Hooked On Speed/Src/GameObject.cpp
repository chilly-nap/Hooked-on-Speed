#pragma once

#include "GameObject.h"

// Constructor that initializes rigidity and hitbox status
GameObject::GameObject(bool isRigid, bool hasHitbox)
{
    mIsRigid = isRigid;     // Set whether the object is rigid
    mHasHitbox = hasHitbox; // Set whether the object has a hitbox
}

// Get the object's hitbox for collision detection
SDL_Rect GameObject::getHitbox() const {
    return mCollider; // Return the collider for the object
}

// Check for collision with another object based on their hitboxes (if enabled)
bool GameObject::checkCollision(SDL_Rect& camera, SDL_Rect& other) const
{
    // Use SDL_HasIntersection to determine if the two rectangles intersect
    return (SDL_HasIntersection(&camera, &other));
}

// Set the position of the object on the screen
void GameObject::setPosition(int x, int y)
{
    mX = x; // Set the X position
    mY = y; // Set the Y position
}

// Check if the object is rigid (i.e., static or immovable)
bool GameObject::isRigid() const {
    return mIsRigid; // Return the rigidity status
}

// Check if the object has a hitbox for collision detection
bool GameObject::hasHitbox() const {
    return mHasHitbox; // Return the hitbox status
}