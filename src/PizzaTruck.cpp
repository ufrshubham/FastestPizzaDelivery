#include "PizzaTruck.hpp"
#include "AssetManager.hpp"

PizzaTruck::PizzaTruck(const AssetManager &assetManager, const Vector3 &position)
{
    this->SetPosition(position);
    m_truckModel = assetManager.Get(AssetId::PizzaTruck);
}

void PizzaTruck::ProcessInputs()
{
    m_speed = 0.f;
    auto position = this->GetPosition();
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        if (position.z > -10)
        {
            m_speed = -STEER_SPEED;
        }
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        if (position.z < 10)
        {
            m_speed = STEER_SPEED;
        }
    }
}

void PizzaTruck::Update(float deltaTime)
{
    if (m_truckRoll > 2 || m_truckRoll < -2)
    {
        m_deltaRoll = -1 * m_deltaRoll;
    }
    m_truckRoll += m_deltaRoll;

    auto position = this->GetPosition();
    if (position.y > 0.5 || position.y < -0.1)
    {
        m_deltaY = -1 * m_deltaY;
    }

    this->Move({0.f,
                m_deltaY * deltaTime, m_speed * deltaTime});
}

void PizzaTruck::Draw() const
{
    DrawModelEx(m_truckModel, this->GetPosition(), {1.f, 0.f, 0.f}, m_truckRoll, this->GetScale(), WHITE);
}
