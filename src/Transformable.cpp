#include "Transformable.hpp"
#include "raymath.h"

Transformable::Transformable(const Vector3 &position) : m_position(position)
{
}

Vector3 Transformable::GetPosition() const
{
    return m_position;
}

void Transformable::SetPosition(const Vector3 &position)
{
    m_position = position;
}

Vector3 Transformable::GetScale() const
{
    return m_scale;
}

void Transformable::SetScale(const Vector3 &scale)
{
    m_scale = scale;
}

void Transformable::SetScale(float scale)
{
    m_scale = Vector3Scale(m_scale, scale);
}

void Transformable::Move(const Vector3 &offset)
{
    m_position = Vector3Add(m_position, offset);
}

bool Transformable::IsResettable() const
{
    return false;
}

void Transformable::ResetPosition()
{
    if (IsResettable())
    {
        m_position.x = 500.f;
    }
}
