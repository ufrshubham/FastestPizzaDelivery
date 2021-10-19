#pragma once

#include "Entity.hpp"
#include "Transformable.hpp"
#include "IDrawable.hpp"
#include "ICollidable.hpp"

#include "raylib.h"

class AssetManager;
class Game;

// This class represents a house in game world.
class House : public Entity, public Transformable, public IDrawable, public ICollidable
{
public:
    House(const AssetManager &assetManager, const Vector3 &position, const Vector3 &scale, Game *game);

    void Update(float deltaTime) override final;
    void Draw() const override final;

    const BoundingBox &GetCollisionBox() const;

    unsigned int GetCollisionLayers() const override final;
    unsigned int GetCollidableLayers() const override final;
    EntityType GetEntityType() const override final;

private:
    Model m_houseModel = {};

    // Todo: Does not belong here. Better to extract it out as world speed.
    float m_speed = 80.f;

    BoundingBox m_boundingBox = {};
    BoundingBox m_collisionBox = {};

    Vector3 m_initialPosition = {0.f, 0.f, 0.f};
};
