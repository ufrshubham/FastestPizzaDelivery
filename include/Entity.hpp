#pragma once

// This class represents a game entity.
class Entity
{
public:
    virtual ~Entity(){};

    virtual void ProcessInputs(){};
    virtual void Update(float deltaTime){};

    // If this method returns true, current entity
    // will be removed from the game world.
    virtual bool ShouldDestroy() const { return false; };
};
