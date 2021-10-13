#include "Entity.hpp"
#include "Game.hpp"

Entity::Entity(Game *game) : m_game(game)
{
}

void Entity::ProcessInputs()
{
}

void Entity::Update(float deltaTime)
{
}

bool Entity::ShouldDestroy() const
{
    return false;
}

void Entity::AddCommand(const Command &command)
{
    m_game->AddCommand(command);
}
