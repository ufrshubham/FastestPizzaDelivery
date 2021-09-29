#include "Pizza.hpp"
#include "AssetManager.hpp"

#include "raymath.h"
#include "iostream"

Pizza::Pizza(const AssetManager &assetManager, const Vector3 &position, const Vector3 &target) : m_target(Vector3Normalize(target))
{
    this->SetPosition(position);
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

bool Pizza::ShouldDestroy() const
{
    auto pos = this->GetPosition();
    // While traveling along +z(right of truck) sometimes y keeps on increasing.
    // This is a hack for such cases.
    return ((pos.y < 0.f) || (pos.y > 50.f));
}
