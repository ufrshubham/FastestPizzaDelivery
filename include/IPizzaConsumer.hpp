#pragma once

class IPizzaConsumer
{
public:
    virtual ~IPizzaConsumer() {}

    virtual bool WantsPizza() const = 0;
};
