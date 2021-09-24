#include "Game.hpp"

#include <filesystem>

// This function changes cwd to a location which contains the resources folder.
// This implementation is rather questionable.
static void modifyCurrentWorkingDirectory()
{
    while (!std::filesystem::exists("resources"))
    {
        std::filesystem::current_path(std::filesystem::current_path().parent_path());
    }
    auto cwd = std::filesystem::current_path();
}

int main(void)
{
    modifyCurrentWorkingDirectory();

    Game game;
    game.Run();

    return 0;
}
