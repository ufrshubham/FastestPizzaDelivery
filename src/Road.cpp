#include "Road.hpp"

#include "raylib.h"

Road::Road()
{
    int count = 0;
    Vector3 position = {0.f, 0.01f, 0.f};

    for (auto &strip : m_roadStrips)
    {
        position.x += 30;
        strip.SetPosition(position);
    }
}

void Road::Update(float deltaTime)
{
    for (auto &strip : m_roadStrips)
    {
        strip.Update(deltaTime);

        if (strip.GetPosition().x < -10)
        {

        }
    }
}

void Road::Draw() const
{
    DrawPlane(ROAD_POSITION, ROAD_SIZE, ROAD_COLOR);
    for (const auto &strip : m_roadStrips)
    {
        strip.Draw();
    }
}

void RoadStrip::Update(float deltaTime)
{
    m_stripPosition.x -= 1.f;
}

void RoadStrip::Draw() const
{
    DrawPlane(m_stripPosition, STRIP_SIZE, STRIP_COLOR);
}

Vector3 RoadStrip::GetPosition() const
{
    return m_stripPosition;
}

void RoadStrip::SetPosition(Vector3 position)
{
    m_stripPosition = position;
}
