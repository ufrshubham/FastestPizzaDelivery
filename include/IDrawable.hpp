#pragma once

// All drawable entities should implement this interface.
class IDrawable
{
public:
    virtual void Draw() const = 0;
};
