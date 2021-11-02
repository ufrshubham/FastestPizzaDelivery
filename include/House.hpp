#pragma once

#include "Entity.hpp"
#include "Transformable.hpp"
#include "IDrawable.hpp"
#include "ICollidable.hpp"
#include "IPizzaConsumer.hpp"
#include "OrderPlacer.hpp"

#include "raylib.h"

class AssetManager;
class Game;

// This class represents a house in game world.
class House : public Entity, public Transformable, public IDrawable, public ICollidable, public IPizzaConsumer
{
public:
    House(const AssetManager &assetManager, const Vector3 &position, const Vector3 &scale, Game *game);

    void Update(float deltaTime) override final;
    void Draw() const override final;

    const BoundingBox &GetCollisionBox() const override final;
    void OnCollision(const ICollidable &otherCollidable) override final;

    unsigned int GetCollisionLayers() const override final;
    unsigned int GetCollidableLayers() const override final;

    EntityType GetEntityType() const override final;

    bool IsResettable() const override final;

    bool WantsPizza() const override final;

private:
    Model m_houseModel = {};

    // Todo: Does not belong here. Better to extract it out as world speed.
    float m_speed = 80.f;
    float m_orderIndicatorSpeed = 10.f;
    float m_orderIndicatorOffset = 15.f;

    bool m_wantsPizza = false;

    BoundingBox m_boundingBox = {};
    BoundingBox m_collisionBox = {};
    OrderPlacer m_orderPlacer;
};
