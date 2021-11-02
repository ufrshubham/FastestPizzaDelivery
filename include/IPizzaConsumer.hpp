#pragma once

class IPizzaConsumer
{
public:
    IPizzaConsumer() = default;
    virtual ~IPizzaConsumer() {}

    virtual bool WantsPizza() const = 0;
};
