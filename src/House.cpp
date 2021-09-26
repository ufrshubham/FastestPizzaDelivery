#include "House.hpp"
#include "AssetManager.hpp"

House::House(const AssetManager &assetManager, const Vector3 &position, const Vector3 &scale) : m_initialPosition(position)
{
    this->SetPosition(position);
    this->SetScale(scale);
    // Todo: Need to improve this.
    m_initialPosition.x = 500.0f;
    m_houseModel = assetManager.Get(AssetId::House);
}

void House::Update(float deltaTime)
{
    this->Move({-m_speed * deltaTime, 0.f, 0.f});

    if (this->GetPosition().x < -40)
    {
        this->SetPosition(m_initialPosition);
    }
}

void House::Draw() const
{
    DrawModelEx(m_houseModel, this->GetPosition(), {1.f, 0.f, 0.f}, 0.f, this->GetScale(), WHITE);
}
