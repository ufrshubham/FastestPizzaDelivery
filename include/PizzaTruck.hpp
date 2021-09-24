#pragma once

#include "Entity.hpp"
#include "IDrawable.hpp"

#include "raylib.h"

class AssetManager;

// This class represents the PizzaTrick in game world.
class PizzaTruck : public Entity, public IDrawable
{
public:
    PizzaTruck(const AssetManager &assetManager);

    void ProcessInputs() override final;
    void Update(float deltaTime) override final;
    void Draw() const override final;

private:
    Model m_truckModel = {};
    Vector3 m_pizzaTruckPosition = {0.0f, 0.0f, 0.0f};
    float m_truckRoll = 0.f;
    float m_deltaRoll = 0.09f;
    float m_deltaY = 0.02f;
    const float STEER_SPEED = 0.5f;
};
