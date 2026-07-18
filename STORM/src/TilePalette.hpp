#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Tileset.hpp"



class TilePalette
{
private:

    Tileset* tileset = nullptr;


    std::vector<int> tileIDs;


    int selected = 1;


    sf::Vector2f position =
        sf::Vector2f(10.f, 10.f);


    int tileSize = 16;


    int spacing = 8;


public:


    void load(
        Tileset& tileset
    );


    void draw(
        sf::RenderWindow& window
    );


    void handleClick(
        sf::Vector2i mouse
    );


    int getSelected() const;

};