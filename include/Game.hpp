#pragma once

#include "raylib.h"

#include <forward_list>
#include <memory>

class Entity;
class AssetManager;
class Transformable;

// This is the main game class which start the game.
class Game
{
public:
    Game();
    virtual ~Game();

    void Run();

private:
    // All the input handling will be done here.
    void ProcessInputs();

    // Gets called every frame of the game.
    void Update(float deltaTime);

    // Draws everything on the game window.
    void Draw() const;

private:
    const int SCREEN_WIDTH = 1920 / 2;
    const int SCREEN_HEIGHT = 1080 / 2;
    const char *TITLE = "Fastest Pizza Delivery : Engine Less Jam";

    float m_worldSpeed = 10.f;

    bool m_isCameraShaking = false;
    float m_cameraShakeTimer = 0.f;

    Camera3D m_camera = {};
    const Vector3 m_initialTargetPosition = {6.0f, 0.0f, 0.0f};

    std::unique_ptr<AssetManager> m_assetManager;
    std::forward_list<std::unique_ptr<Entity>> m_entities;
    Transformable *m_pizzaTruck = nullptr;

    bool m_isPaused = false;
};
