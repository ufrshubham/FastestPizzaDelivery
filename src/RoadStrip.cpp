#include "RoadStrip.hpp"

void RoadStrip::Update(float deltaTime)
{
    this->Move({-m_speed * deltaTime, 0.f, 0.f});
}

void RoadStrip::Draw() const
{
    DrawPlane(this->GetPosition(), STRIP_SIZE, STRIP_COLOR);
}
