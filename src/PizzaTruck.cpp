#include "PizzaTruck.hpp"
#include "AssetManager.hpp"

PizzaTruck::PizzaTruck(const AssetManager &assetManager, const Vector3 &position)
    : m_position(position)
{
    m_truckModel = assetManager.Get(AssetId::PizzaTruck);
}

void PizzaTruck::ProcessInputs()
{
    m_speed = 0.f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        if (m_position.z > -10)
        {
            m_speed = -STEER_SPEED;
        }
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        if (m_position.z < 10)
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

    if (m_position.y > 0.5 || m_position.y < -0.1)
    {
        m_deltaY = -1 * m_deltaY;
    }

    m_position.y += m_deltaY * deltaTime;

    m_position.z += m_speed * deltaTime;
}

void PizzaTruck::Draw() const
{
    DrawModelEx(m_truckModel, m_position, {1.f, 0.f, 0.f}, m_truckRoll, {1.f, 1.f, 1.f}, WHITE);
}
