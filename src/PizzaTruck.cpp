#include "PizzaTruck.hpp"
#include "AssetManager.hpp"

PizzaTruck::PizzaTruck(const AssetManager &assetManager)
{
    m_truckModel = assetManager.Get(AssetId::PizzaTruck);
}

void PizzaTruck::ProcessInputs()
{
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        if (m_pizzaTruckPosition.z > -10)
        {
            m_pizzaTruckPosition.z -= STEER_SPEED;
        }
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        if (m_pizzaTruckPosition.z < 10)
        {
            m_pizzaTruckPosition.z += STEER_SPEED;
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

    if (m_pizzaTruckPosition.y > 0.5 || m_pizzaTruckPosition.y < -0.1)
    {
        m_deltaY = -1 * m_deltaY;
    }

    m_pizzaTruckPosition.y += m_deltaY;
}

void PizzaTruck::Draw() const
{
    DrawModelEx(m_truckModel, m_pizzaTruckPosition, {1.f, 0.f, 0.f}, m_truckRoll, {1.f, 1.f, 1.f}, WHITE);
}
