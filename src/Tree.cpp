#include "Tree.hpp"
#include "AssetManager.hpp"

TreeSmall::TreeSmall(const AssetManager &assetManager, const Vector3 &position) : m_position(position), m_initialPosition(position)
{
    m_treeModel = assetManager.Get(AssetId::TreeSmall);
}

void TreeSmall::Update(float deltaTime)
{
    m_position.x -= m_speed * deltaTime;

    if (m_position.x < -40)
    {
        m_position = m_initialPosition;
    }
}

void TreeSmall::Draw() const
{
    DrawModelEx(m_treeModel, m_position, {1.f, 0.f, 0.f}, 0.f, {20.f, 20.f, 20.f}, WHITE);
}
