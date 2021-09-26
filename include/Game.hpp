#pragma once

#include "raylib.h"

#include <vector>
#include <memory>

class Entity;
class AssetManager;

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

    Camera3D m_camera = {};
    Vector3 m_roadStripPosition = {40.f, 0.01f, 0.f};

    std::unique_ptr<AssetManager> m_assetManager;
    std::vector<std::unique_ptr<Entity>> m_entities;

    bool m_isPaused = false;
};
