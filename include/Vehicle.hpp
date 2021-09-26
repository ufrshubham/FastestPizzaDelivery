#pragma once

#include "Entity.hpp"
#include "Transformable.hpp"
#include "IDrawable.hpp"
#include "AssetManager.hpp"

#include "raylib.h"

enum class VehicleType
{
    Car
};

class Vehicle : public Entity, public Transformable, public IDrawable
{
public:
    Vehicle(const AssetManager &assetManager, VehicleType vehicleType, const Vector3 &position, const Vector3 &scale);

    void Update(float deltaTime) override final;
    void Draw() const override final;

private:
    Model m_model = {};
    BoundingBox m_boundingBox = {};
    BoundingBox m_collisionBox = {};

    float m_speed = 110.f;
    Vector3 m_initialPosition = {0.f, 0.f, 0.f};
};
