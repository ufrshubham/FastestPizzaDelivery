#include "RoadStrip.hpp"

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
