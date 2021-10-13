#pragma once

#include "Entity.hpp"
#include "Transformable.hpp"
#include "IDrawable.hpp"
#include "ICollidable.hpp"

#include "raylib.h"

class AssetManager;
class Game;

// This class represents the PizzaTrick in game world.
class PizzaTruck : public Entity, public Transformable, public IDrawable, public ICollidable
{
public:
    PizzaTruck(const AssetManager &assetManager, const Vector3 &position, Game *game);

    void ProcessInputs() override final;
    void Update(float deltaTime) override final;
    void Draw() const override final;

    const BoundingBox &GetCollisionBox() const override final;

    unsigned int GetCollisionLayers() const override final;
    unsigned int GetCollidableLayers() const override final;

    void IncreaseScore(int points);
    int GetScore() const;

private:
    Model m_truckModel = {};
    BoundingBox m_boundingBox = {};
    BoundingBox m_collisionBox = {};

    float m_speed = 0.f;
    float m_truckRoll = 0.f;
    float m_deltaRoll = 0.09f;
    float m_deltaY = 1.2f;
    int m_score = 0;

    const float STEER_SPEED = 30.f;
};
