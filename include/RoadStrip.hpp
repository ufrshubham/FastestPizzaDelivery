#pragma once

#include "Entity.hpp"
#include "IDrawable.hpp"

#include "raylib.h"

// This class represents the white strip on road.
class RoadStrip : public Entity,
                  public IDrawable
{
public:
    void Update(float deltaTime) override final;
    void Draw() const override final;

    Vector3 GetPosition() const;
    void SetPosition(Vector3 position);

private:
    Vector3 m_stripPosition = {200.f,
                               0.f,
                               0.f};
    const Vector2 STRIP_SIZE = {20.f, 1.f};
    const Color STRIP_COLOR = WHITE;
};
