#pragma once

#include "Transformable.hpp"
#include "IDrawable.hpp"

#include "raylib.h"

class Game;

// This class represents the white strip on road.
class RoadStrip : public Transformable,
                  public IDrawable
{
public:
    void Update(float deltaTime);
    void Draw() const;

private:
    float m_speed = 80.f;
    ;
    const Vector2 STRIP_SIZE = {20.f, 1.f};
    const Color STRIP_COLOR = WHITE;
};
