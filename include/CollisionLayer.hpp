#pragma once

enum CollisionLayer
{
    PizzaLayer = 1 << 0,
    VehicleLayer = 1 << 1,
    BuildingLayer = 1 << 2,
    PizzaTruckLayer = 1 << 3,
};
