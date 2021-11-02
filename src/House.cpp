#include "House.hpp"
#include "AssetManager.hpp"
#include "CollisionLayer.hpp"
#include "Pizza.hpp"
#include "PizzaTruck.hpp"

#include "raymath.h"

House::House(const AssetManager &assetManager, const Vector3 &position, const Vector3 &scale, Game *game)
    : Entity(game), Transformable(position), m_orderPlacer(std::pair(3, 6), std::pair(5, 8))
{
    this->SetScale(scale);
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
    m_wantsPizza = m_orderPlacer.ShouldPlaceOrder(deltaTime, m_wantsPizza);

    this->Move({-m_speed * deltaTime, 0.f, 0.f});

    m_collisionBox.max = Vector3Subtract(Vector3Add(m_boundingBox.max, this->GetPosition()), {0.f, 0.f, 0.f});
    m_collisionBox.min = Vector3Add(Vector3Add(m_boundingBox.min, this->GetPosition()), {0.f, 0.f, 0.f});
}

void House::Draw() const
{
    if (this->WantsPizza())
    {
        auto markerPos = Vector3Add(this->GetPosition(), {0.f, 15.f, 0.f});
        DrawCylinder(markerPos, 2.f, 0.f, 3.0f, 8, BLACK);
    }

    DrawModelEx(m_houseModel, this->GetPosition(), {1.f, 0.f, 0.f}, 0.f, this->GetScale(), WHITE);
#ifdef SHOW_COLLISION_BOXES
    DrawBoundingBox(m_collisionBox, BLACK);
#endif
}

const BoundingBox &House::GetCollisionBox() const
{
    return m_collisionBox;
}

void House::OnCollision(const ICollidable &otherCollidable)
{
    auto *ptr = &otherCollidable;
    if (dynamic_cast<const Pizza *>(ptr))
    {
        int points = 0;
        Command addToScore;
        addToScore.type = EntityType::PizzaTruck;
        if (m_wantsPizza)
        {
            points = 10;
            m_wantsPizza = false;
        }
        else
        {
            points = -5;
        }

        addToScore.action = [points](Entity &entity)
        {
            auto pizzaTruck = dynamic_cast<PizzaTruck *>(&entity);
            if (pizzaTruck)
            {
                pizzaTruck->AddToScore(points);
            }
        };
        this->AddCommand(addToScore);
    }
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

bool House::IsResettable() const
{
    return true;
}

bool House::WantsPizza() const
{
    return m_wantsPizza;
}