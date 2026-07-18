#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>


class Tileset
{
private:

    std::map<int, sf::Texture> textures;


public:

    bool load(
        const std::string& jsonPath
    );


    const sf::Texture* getTexture(
        int id
    ) const;

    std::vector<int> getIDs() const;


    bool hasTile(
        int id
    ) const;


    int getTileCount() const;

};