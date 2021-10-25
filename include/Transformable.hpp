#pragma once

#include "raylib.h"

class Transformable
{
public:
    Transformable() = default;
    Transformable(const Vector3 &position);
    virtual ~Transformable() = default;

    Vector3 GetPosition() const;
    void SetPosition(const Vector3 &position);

    Vector3 GetScale() const;
    void SetScale(const Vector3 &scale);
    void SetScale(float scale);

    void Move(const Vector3 &offset);
    void ResetPosition();

    virtual bool IsResettable() const;

private:
    Vector3 m_position = {};
    Vector3 m_initialPosition = {};
    Vector3 m_scale = {1.f, 1.f, 1.f};
};
