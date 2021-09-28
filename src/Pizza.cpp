#include "Pizza.hpp"
#include "AssetManager.hpp"

#include "raymath.h"

Pizza::Pizza(const AssetManager &assetManager, const Vector3 &target) : m_target(Vector3Normalize(target))
{
    this->SetPosition({0.f, 10.f, 0.f});
    m_pizzaModel = assetManager.Get(AssetId::Pizza);
}

void Pizza::Update(float deltaTime)
{
    const int speed = 100;
    const int gravity = 4;

    this->Move({m_target.x * speed * deltaTime, ((m_target.y * speed - gravity) * deltaTime), m_target.z * speed * deltaTime});
}

void Pizza::Draw() const
{
    DrawModelEx(m_pizzaModel, this->GetPosition(), {0.f, 0.f, 0.f}, 0.f, {0.5f, 0.5f, 0.5f}, WHITE);
}
