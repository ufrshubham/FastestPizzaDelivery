#pragma once

#include <functional>

class Entity;

enum class EntityType
{
    Pizza,
    PizzaTruck,
    House,
    Vehicle,
    Road,
    Tree,
};

struct Command
{
    std::function<void(Entity &entity)> action;
    EntityType type;
};
