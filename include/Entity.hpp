#pragma once

class Game;
struct Command;

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

private:
    Game *m_game;
};
