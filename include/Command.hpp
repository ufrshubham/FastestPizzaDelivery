#pragma once

#include <functional>

class Entity;

enum class EntityType
{
    Pizza,
    PizzaTruck,
    Houze,
    Vehicle,
};

struct Command
{
    std::function<void(Entity &entity)> action;
    EntityType type;
};
