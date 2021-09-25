#include "Pizza.hpp"
#include "AssetManager.hpp"

Pizza::Pizza(const AssetManager &assetManager)
{
    m_pizzaModel = assetManager.Get(AssetId::Pizza);
}

void Pizza::Update(float deltaTime)
{
    const int gravity = 4;
    m_pizzaPosition.x += m_velocity.x * deltaTime;
    m_pizzaPosition.y += (m_velocity.y * deltaTime) - gravity;
    m_pizzaPosition.z += m_velocity.z * deltaTime;
}

void Pizza::Draw() const
{
    DrawModelEx(m_pizzaModel, m_pizzaPosition, {0.f, 0.f, 0.f}, 0.f, {0.5f, 0.5f, 0.5f}, WHITE);
}
