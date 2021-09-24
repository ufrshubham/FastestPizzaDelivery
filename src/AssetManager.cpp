#include "AssetManager.hpp"

AssetManager::~AssetManager()
{
    for (const auto &asset : m_assetMap)
    {
        UnloadModel(asset.second);
    }
}

void AssetManager::Load(AssetId id, const std::string &path)
{
    m_assetMap[id] = LoadModel("resources/pizza_food_vendor_truck/scene.gltf");
}

Model AssetManager::Get(AssetId id) const
{
    Model model;

    if (m_assetMap.find(id) != m_assetMap.end())
    {
        model = m_assetMap.at(id);
    }

    return model;
}
