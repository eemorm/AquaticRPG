#include <iostream>
#include <filesystem>

#include "Camera.hpp"
#include "InputManager.hpp"
#include "TimeManager.hpp"
#include "AssetManager.hpp"
#include "GameMap.hpp"
#include "TileDatabase.hpp"
#include "MapRenderer.hpp"
#include "Player.hpp"
#include "CollisionManager.hpp"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "AquaticRPG");

    GameMap map;
    map.load("maps/lab.json");

    Collision::map = &map;

    TileDatabase tiles;
    tiles.load("tiles.json");

    MapRenderer renderer;

    Camera camera({854,480});

    camera.getView().setCenter(
        24.f,
        56.f
    );

    camera.zoom(0.5f);

    Input::bind("up", sf::Keyboard::W);
    Input::bind("down", sf::Keyboard::S);
    Input::bind("left", sf::Keyboard::A);
    Input::bind("right", sf::Keyboard::D);

    Player player(Assets::getTexture("assets/textures/dude.png"));
    player.getSprite().setPosition({24.f, 56.f});

    while (window.isOpen()) 
    {
        sf::Event e;
        while (window.pollEvent(e))
            if (e.type == sf::Event::Closed) window.close();

        Input::update();
        Time::update();

        window.clear();
        camera.apply(window);
        camera.follow(player.getSprite().getPosition());
        renderer.draw(window, map, tiles);
        player.update(Time::delta);
        player.draw(window);
        window.display();
    }
}