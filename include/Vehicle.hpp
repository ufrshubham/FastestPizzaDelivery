#pragma once

#include "Entity.hpp"
#include "Transformable.hpp"
#include "IDrawable.hpp"
#include "ICollidable.hpp"
#include "AssetManager.hpp"
#include "IPizzaConsumer.hpp"

#include "raylib.h"

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

private:
    Model m_model = {};
    BoundingBox m_boundingBox = {};
    BoundingBox m_collisionBox = {};

    float m_speed = 110.f;
    Vector3 m_initialPosition = {0.f, 0.f, 0.f};
    bool m_wantsPizza = false;
};
