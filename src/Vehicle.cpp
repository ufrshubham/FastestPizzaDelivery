#include "Vehicle.hpp"
#include "CollisionLayer.hpp"
#include "Pizza.hpp"

#include "raymath.h"

#include <unordered_map>

Vehicle::Vehicle(const AssetManager &assetManager, VehicleType vehicleType, const Vector3 &position, const Vector3 &scale) : m_initialPosition(position)
{
    m_wantsPizza = true;

    static const std::unordered_map<VehicleType, AssetId> typeToAssetId{{VehicleType::Car, AssetId::Car}};
    this->SetPosition(position);
    this->SetScale(scale);
    // Todo: Need to improve this.
    m_initialPosition.x = 500.0f;
    m_model = assetManager.Get(typeToAssetId.at(vehicleType));

    Vector3 boundingBoxMax = {};
    Vector3 boundingBoxMin = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};

    for (int i = 0; i < m_model.meshCount; ++i)
    {
        auto mesh = m_model.meshes[i];
        auto boundingBox = MeshBoundingBox(mesh);

        boundingBoxMax = Vector3Max(boundingBox.max, boundingBoxMax);
        boundingBoxMin = Vector3Min(boundingBox.min, boundingBoxMin);
    }

    m_boundingBox = {Vector3Scale(boundingBoxMin, scale.x), Vector3Scale(boundingBoxMax, scale.x)};
    m_collisionBox = m_boundingBox;
}

void Vehicle::Update(float deltaTime)
{
    this->Move({-m_speed * deltaTime, 0.f, 0.f});

    if (this->GetPosition().x < -40)
    {
        this->SetPosition(m_initialPosition);
    }

    m_collisionBox.max = Vector3Subtract(Vector3Add(m_boundingBox.max, this->GetPosition()), {0.f, 0.f, 0.f});
    m_collisionBox.min = Vector3Add(Vector3Add(m_boundingBox.min, this->GetPosition()), {0.f, 0.f, 0.f});
}

void Vehicle::Draw() const
{
    if (this->WantsPizza())
    {
        auto markerPos = Vector3Add(this->GetPosition(), {0.f, 5.f, 0.f});
        DrawCylinder(markerPos, 2.f, 0.f, 3.0f, 8, BLACK);
    }

    DrawModelEx(m_model, this->GetPosition(), {0.f, 0.f, 0.f}, 0.f, this->GetScale(), WHITE);
#ifdef SHOW_COLLISION_BOXES
    DrawBoundingBox(m_collisionBox, BLACK);
#endif
}

const BoundingBox &Vehicle::GetCollisionBox() const
{
    return m_collisionBox;
}

void Vehicle::OnCollision(const ICollidable &otherCollidable)
{
    auto *ptr = &otherCollidable;
    if (dynamic_cast<const Pizza *>(ptr))
    {
        m_wantsPizza = false;
    }
}

unsigned int Vehicle::GetCollisionLayers() const
{
    return CollisionLayer::VehicleLayer;
}

unsigned int Vehicle::GetCollidableLayers() const
{
    return CollisionLayer::PizzaLayer | CollisionLayer::PizzaTruckLayer;
}

bool Vehicle::WantsPizza() const
{
    return m_wantsPizza;
}
