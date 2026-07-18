#pragma once

#include <SFML/Graphics.hpp>
#include <string>


struct Tile
{
    int id;

    std::string name;

    sf::Texture texture;

    sf::Sprite sprite;


    Tile(
        int id,
        const std::string& path
    )
    :
    id(id),
    name(path)
    {
        texture.loadFromFile(path);
        texture.setSmooth(false);

        sprite.setTexture(texture);
    }
};