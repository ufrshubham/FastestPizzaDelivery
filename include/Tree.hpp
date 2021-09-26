#pragma once

#include "Entity.hpp"
#include "Transformable.hpp"
#include "IDrawable.hpp"

#include "raylib.h"

class AssetManager;

// This class represents a house in game world.
class TreeSmall : public Entity, public Transformable, public IDrawable
{
public:
    TreeSmall(const AssetManager &assetManager, const Vector3 &position, const Vector3 &scale);

    void Update(float deltaTime) override final;
    void Draw() const override final;

private:
    Model m_treeModel = {};

    float m_speed = 80.f;
    Vector3 m_initialPosition = {0.f, 0.f, 0.f};
};
