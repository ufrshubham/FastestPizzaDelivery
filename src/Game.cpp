#include "Game.hpp"
#include "AssetManager.hpp"
#include "PizzaTruck.hpp"
#include "Road.hpp"
#include "Pizza.hpp"
#include "House.hpp"
#include "Tree.hpp"
#include "Vehicle.hpp"
#include "CollisionLayer.hpp"
#include "IPizzaConsumer.hpp"

#include "raylib.h"

#include <sstream>

Game::Game() : m_assetManager(std::make_unique<AssetManager>())
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    //SetWindowState(FLAG_FULLSCREEN_MODE);

    m_camera.position = {-30.f, 16.0f, 0.0f};  // {-25.f, 18.0f, 25.0f}; // Camera position. Alt-position {-30.f, 16.0f, 0.0f}
    m_camera.target = m_initialTargetPosition; // Camera looking at point
    m_camera.up = {0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
    m_camera.fovy = 45.0f;                     // Camera field-of-view Y
    m_camera.projection = CAMERA_PERSPECTIVE;  // Camera mode type

    SetCameraMode(m_camera, CAMERA_CUSTOM);
    SetTargetFPS(60);

    m_assetManager->Load(AssetId::PizzaTruck, "resources/models/pizza_food_vendor_truck/scene.gltf");
    m_assetManager->Load(AssetId::Pizza, "resources/models/pizza/scene.gltf");
    m_assetManager->Load(AssetId::House, "resources/models/houses/house_type04.gltf");
    m_assetManager->Load(AssetId::TreeSmall, "resources/models/trees/treeSmall.gltf");
    m_assetManager->Load(AssetId::Car, "resources/models/vehicles/low-poly_car/car.gltf");

    m_entities.push_front(std::make_unique<Road>(Vector3{450.f,
                                                         0.f,
                                                         0.f},
                                                 this));

    auto ptr = std::make_unique<PizzaTruck>(*m_assetManager, Vector3{0.0f, 0.0f, 0.0f}, this);
    m_pizzaTruck = ptr.get();

    m_entities.push_front(std::move(ptr));
    m_entities.push_front(std::make_unique<House>(*m_assetManager, Vector3{600.0f, 0.0f, -15.0f}, Vector3{20.f, 20.f, 20.f}, this));

    m_entities.push_front(std::make_unique<TreeSmall>(*m_assetManager, Vector3{500.0f, 0.0f, -25.0f}, Vector3{20.f, 20.f, 20.f}, this));
    m_entities.push_front(std::make_unique<TreeSmall>(*m_assetManager, Vector3{520.0f, 0.0f, -25.0f}, Vector3{20.f, 20.f, 20.f}, this));
    m_entities.push_front(std::make_unique<TreeSmall>(*m_assetManager, Vector3{550.0f, 0.0f, -30.0f}, Vector3{20.f, 20.f, 20.f}, this));
    m_entities.push_front(std::make_unique<TreeSmall>(*m_assetManager, Vector3{500.0f, 0.0f, -16.0f}, Vector3{20.f, 20.f, 20.f}, this));

    m_entities.push_front(std::make_unique<Vehicle>(*m_assetManager, VehicleType::Car, Vector3{0.0f, 0.0f, 10.0f}, Vector3{3.f, 3.f, 3.f}, this));
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

        // The deltaTime between window init and first frame is generally huge.
        // This happens because loading assets takes time.
        while (deltaTime > TIME_PER_FRAME)
        {
            deltaTime -= TIME_PER_FRAME;

            this->ProcessInputs();
            this->Update(TIME_PER_FRAME);
        }

        this->Draw();
    }
}

void Game::ProcessInputs()
{
    static const auto clickLayers = CollisionLayer::BuildingLayer | CollisionLayer::VehicleLayer;

    if (IsKeyPressed(KEY_P))
    {
        m_isPaused = !m_isPaused;
    }

    Ray ray = {};
    ray = GetMouseRay(GetMousePosition(), m_camera);
    auto hitInfo = GetCollisionRayGround(ray, 0.f);
    Vector3 aimPosition = hitInfo.position;

    for (const auto &entity : m_entities)
    {
        entity->ProcessInputs();

        auto collidable = dynamic_cast<ICollidable *>(entity.get());
        if (collidable && (collidable->GetCollisionLayers() & clickLayers))
        {
            if (CheckCollisionRayBox(ray, collidable->GetCollisionBox()))
            {
                auto transformable = dynamic_cast<Transformable *>(entity.get());
                aimPosition = transformable->GetPosition();
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        auto position = m_pizzaTruck->GetPosition();
        position.y += 10.f;
        m_entities.push_front(std::make_unique<Pizza>(*m_assetManager, position, Vector3{0.5f, 0.5f, 0.5f}, aimPosition, this));
    }
}

void Game::Update(float deltaTime)
{

    UpdateCamera(&m_camera);

    if (!m_isPaused)
    {
        if (m_cameraShakeTimer > 0.f)
        {
            m_cameraShakeTimer -= deltaTime;
        }
        else if (m_isCameraShaking)
        {
            m_isCameraShaking = false;
            m_camera.target = m_initialTargetPosition;
        }

        std::forward_list<ICollidable *> collidables;

        for (const auto &entity : m_entities)
        {
            entity->Update(deltaTime);

            // Collect all the collidable entities.
            auto collidable = dynamic_cast<ICollidable *>(entity.get());
            if (collidable)
            {
                collidables.push_front(collidable);
            }

            // Reset all transformables
            auto transformable = dynamic_cast<Transformable *>(entity.get());
            if (transformable && (transformable->IsResettable()) && (transformable->GetPosition().x < -40.f))
            {
                transformable->ResetPosition();
            }
        }

        // Perform collision detection.
        this->CheckCollisions(collidables);

        // Process the command queue.
        while (!m_commands.empty())
        {
            auto &command = m_commands.front();

            for (auto &entity : m_entities)
            {
                if (entity->GetEntityType() == command.type)
                {
                    command.action(*entity);
                }
            }
            m_commands.pop();
        }

        // Remove any entity that is marked for deletion.
        m_entities.remove_if([](const auto &entity)
                             { return entity->ShouldDestroy(); });

        if (m_isCameraShaking)
        {
            m_camera.target.y += GetRandomValue(-1, 1) * 0.3f;
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

    std::stringstream ss;
    ss << "Score: " << (dynamic_cast<PizzaTruck *>(m_pizzaTruck))->GetScore();
    DrawText(ss.str().c_str(), 32, 32, 30, RAYWHITE);

    EndDrawing();
}

void Game::CheckCollisions(const std::forward_list<ICollidable *> &collidables)
{
    for (auto entityA : collidables)
    {
        for (auto entityB : collidables)
        {
            if (entityA != entityB)
            {
                if (entityA->GetCollidableLayers() & entityB->GetCollisionLayers())
                {
                    if (CheckCollisionBoxes(entityA->GetCollisionBox(), entityB->GetCollisionBox()))
                    {
                        if (entityA->GetCollisionLayers() & CollisionLayer::PizzaTruckLayer)
                        {
                            m_isCameraShaking = true;
                            m_cameraShakeTimer = 0.5f;
                        }
                        entityA->OnCollision(*entityB);
                    }
                }
            }
        }
    }
}

void Game::AddCommand(const Command &command)
{
    m_commands.push(command);
}
