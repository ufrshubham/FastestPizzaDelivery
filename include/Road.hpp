#pragma once

#include "Entity.hpp"
#include "Transformable.hpp"
#include "RoadStrip.hpp"
#include "IDrawable.hpp"

#include "raylib.h"

#include <array>

// This class represents the road in game world.
class Road : public Entity,
             public Transformable,
             public IDrawable
{
public:
    Road(const Vector3 &position);
    void Update(float deltaTime) override final;
    void Draw() const override final;

private:
    const Vector2 ROAD_SIZE = {1000.f, 30.f};
    const Color ROAD_COLOR = {42, 56, 57, 255};

    static const int NUMBER_OF_ROAD_STRIPS = 12;
    int lastRoadStripIndex = NUMBER_OF_ROAD_STRIPS - 1;
    std::array<RoadStrip, NUMBER_OF_ROAD_STRIPS> m_roadStrips;
};
