#include "Tree.hpp"
#include "AssetManager.hpp"

TreeSmall::TreeSmall(const AssetManager &assetManager, const Vector3 &position, const Vector3 &scale, Game *game) : Entity(game), m_initialPosition(position)
{
    this->SetPosition(position);
    this->SetScale(scale);
    // Todo: Need to improve this.
    m_initialPosition.x = 500.0f;
    m_treeModel = assetManager.Get(AssetId::TreeSmall);
}

void TreeSmall::Update(float deltaTime)
{
    this->Move({-m_speed * deltaTime, 0.f, 0.f});

    if (this->GetPosition().x < -40)
    {
        this->SetPosition(m_initialPosition);
    }
}

void TreeSmall::Draw() const
{
    DrawModelEx(m_treeModel, this->GetPosition(), {1.f, 0.f, 0.f}, 0.f, this->GetScale(), WHITE);
}
