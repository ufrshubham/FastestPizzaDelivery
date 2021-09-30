#pragma once

#include "raylib.h"

// All the collidable entities should implement this interface.
class ICollidable
{
public:
    virtual ~ICollidable(){};

    virtual const BoundingBox &GetCollisionBox() const = 0;
    virtual void OnCollision(const ICollidable &otherCollidable){};

    virtual unsigned int GetCollisionLayers() const = 0;
    virtual unsigned int GetCollidableLayers() const = 0;
};
