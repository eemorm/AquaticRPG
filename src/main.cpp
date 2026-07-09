#include "World.hpp"
#include "Systems.hpp"
#include "Camera.hpp"
#include "TimeManager.hpp"
#include "AssetManager.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS Test");

    Camera cam({800, 600});
    World world;

    // Create player
    Entity player = world.create();
    world.transform[player] = {{100, 200}, {100, 0}};
    world.playerControl[player] = {200.f};
    world.sprite[player] = {sf::Sprite(Assets::getTexture("textures/attack.png"))};
    world.health[player] = {100, 100};
    world.players.insert(player);

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e))
            if (e.type == sf::Event::Closed) window.close();

        Time::update();

        playerControlSystem(world);
        movementSystem(world, Time::delta);

        window.clear();
        //cam.follow(world.transform[player].pos);
        //cam.apply(window);

        renderSystem(world, window);

        window.setView(window.getDefaultView());
        window.display();
    }
}