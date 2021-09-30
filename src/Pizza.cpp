#include "Pizza.hpp"
#include "AssetManager.hpp"

#include "raymath.h"
#include "iostream"

Pizza::Pizza(const AssetManager &assetManager, const Vector3 &position, const Vector3 &target) : m_target(Vector3Normalize(target))
{
    this->SetPosition(position);
    m_pizzaModel = assetManager.Get(AssetId::Pizza);

    m_rotationAxis.x = (float)GetRandomValue(0, 1);
    m_rotationAxis.y = (float)GetRandomValue(0, 1);
    m_rotationAxis.z = (float)GetRandomValue(0, 1);
}

void Pizza::Update(float deltaTime)
{
    const int speed = 100;
    const int gravity = 4;

    m_rotation += 360 * 2 * deltaTime;
    if (m_rotation > 360.f)
    {
        m_rotation = 0.f;
    }

    this->Move({m_target.x * speed * deltaTime, ((m_target.y * speed - gravity) * deltaTime), m_target.z * speed * deltaTime});
}

void Pizza::Draw() const
{
    DrawModelEx(m_pizzaModel, this->GetPosition(), m_rotationAxis, m_rotation, {0.5f, 0.5f, 0.5f}, WHITE);
}

bool Pizza::ShouldDestroy() const
{
    auto pos = this->GetPosition();
    auto lengthSq = Vector3LengthSqr(pos);

    return ((pos.y < 0.f) || (lengthSq > 50000));
}
