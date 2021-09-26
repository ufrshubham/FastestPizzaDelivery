#pragma once

#include "raylib.h"
#include <unordered_map>
#include <string>

// Unique IDs for all the assets used in this  game.
enum class AssetId
{
    PizzaTruck,
    Pizza,
    House,
    TreeSmall,
    Car
};

// This class holds all the assets used in this game.
class AssetManager
{
public:
    AssetManager() = default;
    virtual ~AssetManager();

    AssetManager(const AssetManager &) = delete;
    AssetManager &operator=(const AssetManager &) = delete;

    // Loads the model located at given path and maps it to given AssetId.
    void Load(AssetId id, const std::string &path);

    // Returns the model stored at given AssetId.
    Model Get(AssetId id) const;

private:
    std::unordered_map<AssetId, Model>
        m_assetMap;
};
