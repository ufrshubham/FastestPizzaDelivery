#pragma once

#include "Entity.hpp"
#include "Transformable.hpp"
#include "IDrawable.hpp"

#include "raylib.h"

class AssetManager;

class Pizza : public Entity, public Transformable, public IDrawable
{
public:
    Pizza(const AssetManager &assetManager);

    void Update(float deltaTime) override final;
    void Draw() const override final;

private:
    Model m_pizzaModel = {};
    Vector3 m_velocity = {0.f, 0.f, 0.f};
};
