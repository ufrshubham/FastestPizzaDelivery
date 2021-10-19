#pragma once

class Game;

#include "Command.hpp"

// This class represents a game entity.
class Entity
{
public:
    Entity(Game *game);
    virtual ~Entity() = default;

    virtual void ProcessInputs();
    virtual void Update(float deltaTime);

    // If this method returns true, current entity
    // will be removed from the game world.
    virtual bool ShouldDestroy() const;

    void AddCommand(const Command &command);

    virtual EntityType GetEntityType() const = 0;

private:
    Game *m_game;
    EntityType m_entityType;
};
