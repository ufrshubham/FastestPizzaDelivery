#include "Pizza.hpp"
#include "AssetManager.hpp"
#include "CollisionLayer.hpp"

#include "raymath.h"
#include "iostream"

Pizza::Pizza(const AssetManager &assetManager, const Vector3 &position, const Vector3 &scale, const Vector3 &target, Game *game) : Entity(game), m_target(Vector3Normalize(target))
{
    this->SetPosition(position);
    this->SetScale(scale);
    m_pizzaModel = assetManager.Get(AssetId::Pizza);

    m_rotationAxis.x = (float)GetRandomValue(0, 1);
    m_rotationAxis.y = (float)GetRandomValue(0, 1);
    m_rotationAxis.z = (float)GetRandomValue(0, 1);

    Vector3 boundingBoxMax = {};
    Vector3 boundingBoxMin = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};

    for (int i = 0; i < m_pizzaModel.meshCount; ++i)
    {
        auto mesh = m_pizzaModel.meshes[i];
        auto boundingBox = MeshBoundingBox(mesh);

        boundingBoxMax = Vector3Max(boundingBox.max, boundingBoxMax);
        boundingBoxMin = Vector3Min(boundingBox.min, boundingBoxMin);
    }

    m_boundingBox = {Vector3Scale(boundingBoxMin, scale.x), Vector3Scale(boundingBoxMax, scale.x)};
    m_boundingBox.max.y += 1.f;
    m_boundingBox.min.y -= 2.f;
    m_collisionBox = m_boundingBox;
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

    m_collisionBox.max = Vector3Subtract(Vector3Add(m_boundingBox.max, this->GetPosition()), {0.f, 0.f, 0.f});
    m_collisionBox.min = Vector3Add(Vector3Add(m_boundingBox.min, this->GetPosition()), {0.f, 0.f, 0.f});
}

void Pizza::Draw() const
{
    DrawModelEx(m_pizzaModel, this->GetPosition(), m_rotationAxis, m_rotation, this->GetScale(), WHITE);
#ifdef SHOW_COLLISION_BOXES
    DrawBoundingBox(m_collisionBox, BLACK);
#endif
}

bool Pizza::ShouldDestroy() const
{
    auto pos = this->GetPosition();
    auto lengthSq = Vector3LengthSqr(pos);

    return (m_hasCollided || (pos.y < 0.f) || (lengthSq > 50000));
}

const BoundingBox &Pizza::GetCollisionBox() const
{
    return m_collisionBox;
}

void Pizza::OnCollision(const ICollidable &otherCollidable)
{
    m_hasCollided = true;
}

unsigned int Pizza::GetCollisionLayers() const
{
    return CollisionLayer::PizzaLayer;
}

unsigned int Pizza::GetCollidableLayers() const
{
    return CollisionLayer::VehicleLayer | CollisionLayer::BuildingLayer;
}

EntityType Pizza::GetEntityType() const
{
    return EntityType::Pizza;
}
