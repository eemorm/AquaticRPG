#include "Tileset.hpp"

#include <filesystem>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

bool Tileset::load(const std::string& jsonPath)
{
    textures.clear();

    std::ifstream file(jsonPath);

    if(!file)
        return false;

    json j;
    file >> j;

    for(const auto& tile : j["tiles"])
    {
        int id =
            tile["id"];

        std::string textureName =
            tile["texture"];

        sf::Texture texture;

        if(!texture.loadFromFile(
            "../assets/textures/tiles/" +
            textureName))
        {
            std::cout
                << "Failed loading "
                << textureName
                << "\n";

            continue;
        }

        texture.setSmooth(false);

        textures[id] =
            std::move(texture);

        std::cout
            << id
            << " = "
            << textureName
            << "\n";
    }

    return true;
}




const sf::Texture* Tileset::getTexture(
    int id
) const
{

    auto it =
        textures.find(id);


    if(it == textures.end())
        return nullptr;


    return &it->second;
}


std::vector<int> Tileset::getIDs() const
{
    std::vector<int> ids;

    for(const auto& texture : textures)
    {
        ids.push_back(texture.first);
    }

    std::sort(
        ids.begin(),
        ids.end()
    );

    return ids;
}


bool Tileset::hasTile(
    int id
) const
{
    return textures.count(id);
}





int Tileset::getTileCount() const
{
    return textures.size();
}