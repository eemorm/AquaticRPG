#include <iostream>
#include <filesystem>

#include "Camera.hpp"
#include "TimeManager.hpp"
#include "AssetManager.hpp"
#include "GameMap.hpp"
#include "TileDatabase.hpp"
#include "MapRenderer.hpp"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "AquaticRPG");

    GameMap map;
    map.load("maps/booger.json");

    TileDatabase tiles;
    tiles.load("tiles.json");

    MapRenderer renderer;

    while (window.isOpen()) 
    {
        sf::Event e;
        while (window.pollEvent(e))
            if (e.type == sf::Event::Closed) window.close();

        Time::update();

        window.clear();
        window.setView(window.getDefaultView());
        renderer.draw(window, map, tiles);
        window.display();
    }
}