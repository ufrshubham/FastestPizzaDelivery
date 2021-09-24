#pragma once

// This class represents a game entity.
class Entity
{
public:
    virtual ~Entity(){};

    virtual void ProcessInputs(){};
    virtual void Update(float deltaTime){};
};
