#include "House.hpp"
#include "AssetManager.hpp"

House::House(const AssetManager &assetManager, const Vector3 &position) : m_position(position), m_initialPosition(position)
{
    m_houseModel = assetManager.Get(AssetId::House);
}

void House::Update(float deltaTime)
{
    m_position.x -= m_speed * deltaTime;

    if (m_position.x < -40)
    {
        m_position = m_initialPosition;
    }
}

void House::Draw() const
{
    DrawModelEx(m_houseModel, m_position, {1.f, 0.f, 0.f}, 0.f, {20.f, 20.f, 20.f}, WHITE);
}
