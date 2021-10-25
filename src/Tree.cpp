#include "Tree.hpp"
#include "AssetManager.hpp"

TreeSmall::TreeSmall(const AssetManager &assetManager, const Vector3 &position, const Vector3 &scale, Game *game) : Entity(game)
{
    this->SetPosition(position);
    this->SetScale(scale);
    m_treeModel = assetManager.Get(AssetId::TreeSmall);
}

void TreeSmall::Update(float deltaTime)
{
    this->Move({-m_speed * deltaTime, 0.f, 0.f});
}

void TreeSmall::Draw() const
{
    DrawModelEx(m_treeModel, this->GetPosition(), {1.f, 0.f, 0.f}, 0.f, this->GetScale(), WHITE);
}

EntityType TreeSmall::GetEntityType() const
{
    return EntityType::Tree;
}

bool TreeSmall::IsResettable() const
{
    return true;
}