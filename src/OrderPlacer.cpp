#include "OrderPlacer.hpp"

#include "raylib.h"

OrderPlacer::OrderPlacer(const std::pair<int, int> &orderWaitRange, const std::pair<int, int> &orderIntervalRange)
    : m_pizzaOrderWaitRange(orderWaitRange), m_pizzaOrderIntervalRange(orderIntervalRange)
{
    m_waitTime = GetRandomValue(m_pizzaOrderIntervalRange.first, m_pizzaOrderIntervalRange.second);
}

bool OrderPlacer::ShouldPlaceOrder(float deltaTime, bool wantPizza)
{
    bool shouldPlaceOrder = wantPizza;
    m_elapsedTime += deltaTime;

    if (m_elapsedTime > m_waitTime)
    {
        m_elapsedTime = 0.f;

        if (wantPizza)
        {
            m_waitTime = GetRandomValue(m_pizzaOrderIntervalRange.first, m_pizzaOrderIntervalRange.second);
        }
        else
        {
            m_waitTime = GetRandomValue(m_pizzaOrderWaitRange.first, m_pizzaOrderWaitRange.second);
        }
        shouldPlaceOrder = !shouldPlaceOrder;
    }
    return shouldPlaceOrder;
}
