#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class TileDatabase
{
    private:
        std::unordered_map<int, sf::Texture> textures;
    public:
        bool load(
            const std::string& path
        )
        {
            std::ifstream file(path);

            if(!file)
            {
                std::cout
                    << "Could not open "
                    << path
                    << "\n";

                return false;
            }

            json j;
            file >> j;

            for(auto& tile : j["tiles"])
            {
                int id =
                    tile["id"];

                std::string texturePath =
                    tile["texture"];

                sf::Texture texture;

                if(!texture.loadFromFile(
                    "assets/textures/" + texturePath
                ))
                {
                    std::cout
                        << "Failed loading "
                        << texturePath
                        << "\n";

                    continue;
                }

                textures.emplace(
                    id,
                    std::move(texture)
                );

                std::cout
                    << "Loaded tile "
                    << id
                    << "\n";
            }
            return true;
        }

        sf::Texture& getTexture(
            int id
        )
        {
            return textures.at(id);
        }
};