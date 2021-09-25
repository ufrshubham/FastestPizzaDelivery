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
    m_assetMap[id] = LoadModel(path.c_str());
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
