#pragma once

#include "Entity.hpp"
#include "Transformable.hpp"
#include "IDrawable.hpp"

#include "raylib.h"

// This class represents the white strip on road.
class RoadStrip : public Entity,
                  public Transformable,
                  public IDrawable
{
public:
    void Update(float deltaTime) override final;
    void Draw() const override final;

private:
    float m_speed = 80.f;
    ;
    const Vector2 STRIP_SIZE = {20.f, 1.f};
    const Color STRIP_COLOR = WHITE;
};
