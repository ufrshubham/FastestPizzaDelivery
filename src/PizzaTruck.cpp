#include "PizzaTruck.hpp"
#include "AssetManager.hpp"

#include "raymath.h"
#include <limits>

PizzaTruck::PizzaTruck(const AssetManager &assetManager, const Vector3 &position)
{
    this->SetPosition(position);
    m_truckModel = assetManager.Get(AssetId::PizzaTruck);

    Vector3 boundingBoxMax = {};
    Vector3 boundingBoxMin = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};

    for (int i = 0; i < m_truckModel.meshCount; ++i)
    {
        auto mesh = m_truckModel.meshes[i];
        auto boundingBox = MeshBoundingBox(mesh);

        boundingBoxMax = Vector3Max(boundingBox.max, boundingBoxMax);
        boundingBoxMin = Vector3Min(boundingBox.min, boundingBoxMin);
    }
    m_boundingBox = {boundingBoxMin, boundingBoxMax};
    m_collisionBox = m_boundingBox;
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

    m_collisionBox.max = Vector3Subtract(Vector3Add(m_boundingBox.max, this->GetPosition()), {2.f, 0.f, 2.f});
    m_collisionBox.min = Vector3Add(Vector3Add(m_boundingBox.min, this->GetPosition()), {2.f, 0.f, 2.f});
}

void PizzaTruck::Draw() const
{
    DrawModelEx(m_truckModel, this->GetPosition(), {1.f, 0.f, 0.f}, m_truckRoll, this->GetScale(), WHITE);
#ifdef SHOW_COLLISION_BOXES
    DrawBoundingBox(m_collisionBox, BLACK);
#endif
}

const BoundingBox &PizzaTruck::GetCollisionBox() const
{
    return m_collisionBox;
}
