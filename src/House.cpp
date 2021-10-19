#include "House.hpp"
#include "AssetManager.hpp"
#include "CollisionLayer.hpp"

#include "raymath.h"

House::House(const AssetManager &assetManager, const Vector3 &position, const Vector3 &scale, Game *game) : Entity(game), m_initialPosition(position)
{
    this->SetPosition(position);
    this->SetScale(scale);
    // Todo: Need to improve this.
    m_initialPosition.x = 500.0f;
    m_houseModel = assetManager.Get(AssetId::House);

    Vector3 boundingBoxMax = {};
    Vector3 boundingBoxMin = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};

    for (int i = 0; i < m_houseModel.meshCount; ++i)
    {
        auto mesh = m_houseModel.meshes[i];
        auto boundingBox = MeshBoundingBox(mesh);

        boundingBoxMax = Vector3Max(boundingBox.max, boundingBoxMax);
        boundingBoxMin = Vector3Min(boundingBox.min, boundingBoxMin);
    }

    m_boundingBox = {Vector3Scale(boundingBoxMin, scale.x), Vector3Scale(boundingBoxMax, scale.x)};
    m_collisionBox = m_boundingBox;
}

void House::Update(float deltaTime)
{
    this->Move({-m_speed * deltaTime, 0.f, 0.f});

    if (this->GetPosition().x < -40)
    {
        this->SetPosition(m_initialPosition);
    }

    m_collisionBox.max = Vector3Subtract(Vector3Add(m_boundingBox.max, this->GetPosition()), {0.f, 0.f, 0.f});
    m_collisionBox.min = Vector3Add(Vector3Add(m_boundingBox.min, this->GetPosition()), {0.f, 0.f, 0.f});
}

void House::Draw() const
{
    DrawModelEx(m_houseModel, this->GetPosition(), {1.f, 0.f, 0.f}, 0.f, this->GetScale(), WHITE);
#ifdef SHOW_COLLISION_BOXES
    DrawBoundingBox(m_collisionBox, BLACK);
#endif
}

const BoundingBox &House::GetCollisionBox() const
{
    return m_collisionBox;
}

unsigned int House::GetCollisionLayers() const
{
    return CollisionLayer::BuildingLayer;
}

unsigned int House::GetCollidableLayers() const
{
    return CollisionLayer::PizzaLayer;
}

EntityType House::GetEntityType() const
{
    return EntityType::House;
}
