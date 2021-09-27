#include "Game.hpp"
#include "AssetManager.hpp"
#include "PizzaTruck.hpp"
#include "Road.hpp"
#include "Pizza.hpp"
#include "House.hpp"
#include "Tree.hpp"
#include "Vehicle.hpp"

#include "raylib.h"

Game::Game() : m_assetManager(std::make_unique<AssetManager>())
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

    m_camera.position = m_initialCameraPosition; // Camera position
    m_camera.target = {6.0f, 0.0f, 0.0f};        // Camera looking at point
    m_camera.up = {0.0f, 1.0f, 0.0f};            // Camera up vector (rotation towards target)
    m_camera.fovy = 45.0f;                       // Camera field-of-view Y
    m_camera.projection = CAMERA_PERSPECTIVE;    // Camera mode type

    SetCameraMode(m_camera, CAMERA_FREE);
    SetTargetFPS(60);

    m_assetManager->Load(AssetId::PizzaTruck, "resources/models/pizza_food_vendor_truck/scene.gltf");
    m_assetManager->Load(AssetId::Pizza, "resources/models/pizza/scene.gltf");
    m_assetManager->Load(AssetId::House, "resources/models/houses/house_type04.gltf");
    m_assetManager->Load(AssetId::TreeSmall, "resources/models/trees/treeSmall.gltf");
    m_assetManager->Load(AssetId::Car, "resources/models/vehicles/low-poly_car/car.gltf");

    m_entities.push_back(std::make_unique<Road>(Vector3{200.f,
                                                        0.f,
                                                        0.f}));
    m_entities.push_back(std::make_unique<PizzaTruck>(*m_assetManager, Vector3{0.0f, 0.0f, 0.0f}));
    m_entities.push_back(std::make_unique<House>(*m_assetManager, Vector3{600.0f, 0.0f, -15.0f}, Vector3{20.f, 20.f, 20.f}));

    m_entities.push_back(std::make_unique<TreeSmall>(*m_assetManager, Vector3{500.0f, 0.0f, -25.0f}, Vector3{20.f, 20.f, 20.f}));
    m_entities.push_back(std::make_unique<TreeSmall>(*m_assetManager, Vector3{520.0f, 0.0f, -25.0f}, Vector3{20.f, 20.f, 20.f}));
    m_entities.push_back(std::make_unique<TreeSmall>(*m_assetManager, Vector3{550.0f, 0.0f, -30.0f}, Vector3{20.f, 20.f, 20.f}));
    m_entities.push_back(std::make_unique<TreeSmall>(*m_assetManager, Vector3{500.0f, 0.0f, -16.0f}, Vector3{20.f, 20.f, 20.f}));

    m_entities.push_back(std::make_unique<Vehicle>(*m_assetManager, VehicleType::Car, Vector3{0.0f, 0.0f, 10.0f}, Vector3{3.f, 3.f, 3.f}));
}

Game::~Game()
{
    CloseWindow();
}

void Game::Run()
{
    float deltaTime = 0.f;

    while (!WindowShouldClose())
    {
        deltaTime += GetFrameTime();
        UpdateCamera(&m_camera);

        // The deltaTime between window init and first frame is generally huge.
        // This happens because loading assets takes time.
        while (deltaTime > (1 / 60.f))
        {
            deltaTime -= 1 / 60.f;

            this->ProcessInputs();
            this->Update(1 / 60.f);
        }

        this->Draw();
    }
}

void Game::ProcessInputs()
{
    if (IsKeyPressed(KEY_P))
    {
        // m_entities.push_back(std::make_unique<Pizza>(*m_assetManager));
        m_isPaused = !m_isPaused;
    }

    for (const auto &entity : m_entities)
    {
        entity->ProcessInputs();
    }
}

void Game::Update(float deltaTime)
{
    if (!m_isPaused)
    {
        if (m_cameraShakeTimer > 0.f)
        {
            m_cameraShakeTimer -= deltaTime;
        }
        else
        {
            m_isCameraShaking = false;
            m_camera.position = m_initialCameraPosition;
        }

        std::vector<ICollidable *> m_collidables;

        for (const auto &entity : m_entities)
        {
            entity->Update(deltaTime);

            auto collidable = dynamic_cast<ICollidable *>(entity.get());
            if (collidable)
            {
                m_collidables.push_back(collidable);
            }
        }

        for (auto entityA : m_collidables)
        {
            for (auto entityB : m_collidables)
            {
                if (entityA != entityB)
                {
                    if (CheckCollisionBoxes(entityA->GetCollisionBox(), entityB->GetCollisionBox()))
                    {
                        entityA->OnCollision(*entityB);
                        entityB->OnCollision(*entityA);

                        m_isCameraShaking = true;
                        m_cameraShakeTimer = 0.5f;
                    }
                }
            }
        }

        if (m_isCameraShaking)
        {
            m_camera.position.x += GetRandomValue(-1, 1);
            m_camera.position.y += GetRandomValue(-1, 1);
            m_camera.position.z += GetRandomValue(-1, 1);
        }
    }
}

void Game::Draw() const
{
    BeginDrawing();
    ClearBackground({107, 128, 52, 255});
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
