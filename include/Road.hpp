#pragma once

#include "Entity.hpp"
#include "IDrawable.hpp"

#include "raylib.h"

#include <array>

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

class Road : public Entity,
             public IDrawable
{
public:
    Road();
    void Update(float deltaTime) override final;
    void Draw() const override final;

private:
    const Vector3 ROAD_POSITION = {200.f,
                                   0.f,
                                   0.f};
    const Vector2 ROAD_SIZE = {1000.f, 30.f};
    const Color ROAD_COLOR = DARKGRAY;

    std::array<RoadStrip, 10> m_roadStrips;
};
