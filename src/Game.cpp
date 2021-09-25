#include "Game.hpp"
#include "AssetManager.hpp"
#include "PizzaTruck.hpp"
#include "Road.hpp"
#include "Pizza.hpp"

#include "raylib.h"

Game::Game() : m_assetManager(std::make_unique<AssetManager>())
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

    m_camera.position = {-25.f, 18.0f, 25.0f}; // Camera position
    m_camera.target = {6.0f, 0.0f, 0.0f};      // Camera looking at point
    m_camera.up = {0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
    m_camera.fovy = 45.0f;                     // Camera field-of-view Y
    m_camera.projection = CAMERA_PERSPECTIVE;  // Camera mode type

    SetCameraMode(m_camera, CAMERA_FREE);
    SetTargetFPS(60);

    m_assetManager->Load(AssetId::PizzaTruck, "resources/pizza_food_vendor_truck/scene.gltf");
    m_assetManager->Load(AssetId::Pizza, "resources/pizza/scene.gltf");

    m_entities.push_back(std::make_unique<Road>());
    m_entities.push_back(std::make_unique<PizzaTruck>(*m_assetManager));
}

Game::~Game()
{
    CloseWindow();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        UpdateCamera(&m_camera);

        this->ProcessInputs();
        this->Update(GetFrameTime());
        this->Draw();
    }
}

void Game::ProcessInputs()
{
    if (IsKeyPressed(KEY_P))
    {
        m_entities.push_back(std::make_unique<Pizza>(*m_assetManager));
    }

    for (const auto &entity : m_entities)
    {
        entity->ProcessInputs();
    }
}

void Game::Update(float deltaTime)
{
    for (const auto &entity : m_entities)
    {
        entity->Update(deltaTime);
    }
}

void Game::Draw() const
{
    BeginDrawing();
    ClearBackground(DARKGREEN);
    BeginMode3D(m_camera);

    for (const auto &entity : m_entities)
    {
        auto drawable = dynamic_cast<const IDrawable *>(entity.get());
        if (drawable)
        {
            drawable->Draw();
        }
    }

    EndMode3D();
    EndDrawing();
}
