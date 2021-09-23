#include "raylib.h"
#include <string>
#include <filesystem>

int main(void)
{
    while (!std::filesystem::exists("resources"))
    {
        std::filesystem::current_path(std::filesystem::current_path().parent_path());
    }

    auto cwd = std::filesystem::current_path();

    const int screenWidth = 1920 / 2;
    const int screenHeight = 1080 / 2;
    auto title = "Fastest Pizza Delivery : Engine Less Jam";

    InitWindow(screenWidth, screenHeight, title);
#if defined(PLATFORM_DESKTOP)
    // SetWindowState(FLAG_FULLSCREEN_MODE);
#endif

    // Define the camera to look into our 3d world
    Camera camera = {0};
    camera.position = {-25.f, 18.0f, 25.0f}; // Camera position
    camera.target = {6.0f, 0.0f, 0.0f};      // Camera looking at point
    camera.up = {0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                     // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;  // Camera mode type

    Model model = {};
    model = LoadModel("resources/pizza_food_vendor_truck/scene.gltf");

    Vector3 pizzaTruckPosition = {0.0f, 0.0f, 0.0f};
    SetCameraMode(camera, CAMERA_FREE);
    SetTargetFPS(60);

    const float steerSpeed = 0.5;
    float truckRoll = 0.f;
    float deltaRoll = 0.09f;
    float deltaY = 0.02f;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);

        if (truckRoll > 2 || truckRoll < -2)
        {
            deltaRoll = -1 * deltaRoll;
        }
        truckRoll += deltaRoll;

        if (pizzaTruckPosition.y > 0.5 || pizzaTruckPosition.y < -0.1)
        {
            deltaY = -1 * deltaY;
        }

        pizzaTruckPosition.y += deltaY;

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            if (pizzaTruckPosition.z > -10)
            {
                pizzaTruckPosition.z -= steerSpeed;
            }
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            if (pizzaTruckPosition.z < 10)
            {
                pizzaTruckPosition.z += steerSpeed;
            }
        }

        BeginDrawing();
        ClearBackground(DARKGREEN);
        BeginMode3D(camera);

        DrawPlane({200.f, 0.f, 0.f}, {1000, 30}, DARKGRAY);
        DrawModelEx(model, pizzaTruckPosition, {1.f, 0.f, 0.f}, truckRoll, {1.f, 1.f, 1.f}, WHITE);

        EndMode3D();
        EndDrawing();
    }

    UnloadModel(model);
    CloseWindow();

    return 0;
}
