#include "Road.hpp"

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
    int i = 0;
    for (auto &strip : m_roadStrips)
    {
        strip.Update(deltaTime);

        if (strip.GetPosition().x < -30)
        {
            auto lastRoadStrip = m_roadStrips.at(lastRoadStripIndex);
            auto position = lastRoadStrip.GetPosition();
            position.x += 30.f;

            strip.SetPosition(position);
            lastRoadStripIndex = i;
        }
        ++i;
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
