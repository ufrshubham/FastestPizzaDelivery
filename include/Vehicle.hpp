#pragma once

#include "Entity.hpp"
#include "Transformable.hpp"
#include "IDrawable.hpp"
#include "ICollidable.hpp"
#include "AssetManager.hpp"
#include "IPizzaConsumer.hpp"
#include "OrderPlacer.hpp"

#include "raylib.h"

#include <utility>

class Game;

enum class VehicleType
{
    Car
};

class Vehicle : public Entity, public Transformable, public IDrawable, public ICollidable, public IPizzaConsumer
{
public:
    Vehicle(const AssetManager &assetManager, VehicleType vehicleType, const Vector3 &position, const Vector3 &scale, Game *game);

    void Update(float deltaTime) override final;
    void Draw() const override final;

    const BoundingBox &GetCollisionBox() const override final;
    void OnCollision(const ICollidable &otherCollidable) override final;

    unsigned int GetCollisionLayers() const override final;
    unsigned int GetCollidableLayers() const override final;

    bool WantsPizza() const override final;

    EntityType GetEntityType() const override final;

    bool IsResettable() const override final;

private:
    Model m_model = {};

    float m_speed = 110.f;
    float m_orderIndicatorSpeed = 10.f;
    float m_orderIndicatorOffset = 5.f;

    bool m_wantsPizza = false;

    BoundingBox m_boundingBox = {};
    BoundingBox m_collisionBox = {};
    OrderPlacer m_orderPlacer;
};
