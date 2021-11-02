#pragma once

#include <utility>

class OrderPlacer
{
public:
    OrderPlacer(const std::pair<int, int> &orderWaitRange, const std::pair<int, int> &orderIntervalRange);
    ~OrderPlacer() = default;

    bool ShouldPlaceOrder(float deltaTime, bool wantPizza);

private:
    float m_elapsedTime = 0.f;
    int m_waitTime = 0;

    // How long this entity waits before cancelling the order.
    const std::pair<int, int> m_pizzaOrderWaitRange;

    // How long this entity waits before placing new order.
    const std::pair<int, int> m_pizzaOrderIntervalRange;
};
