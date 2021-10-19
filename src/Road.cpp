#include "Road.hpp"

Road::Road(const Vector3 &position, Game *game) : Entity(game)
{
    this->SetPosition(position);

    int count = 0;
    Vector3 roadStripPosition = {0.f, 0.02f, 0.f};

    for (auto &strip : m_roadStrips)
    {
        roadStripPosition.x += 30;
        strip.SetPosition(roadStripPosition);
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
    DrawPlane(this->GetPosition(), ROAD_SIZE, ROAD_COLOR);
    for (const auto &strip : m_roadStrips)
    {
        strip.Draw();
    }
}

EntityType Road::GetEntityType() const
{
    return EntityType::Road;
}
