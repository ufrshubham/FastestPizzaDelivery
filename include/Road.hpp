#pragma once

#include "Entity.hpp"
#include "IDrawable.hpp"
#include "RoadStrip.hpp"

#include "raylib.h"

#include <array>

// This class represents the road in game world.
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

    static const int NUMBER_OF_ROAD_STRIPS = 12;
    int lastRoadStripIndex = NUMBER_OF_ROAD_STRIPS - 1;
    std::array<RoadStrip, NUMBER_OF_ROAD_STRIPS> m_roadStrips;
};
