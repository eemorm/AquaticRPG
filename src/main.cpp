#include "Camera.hpp"
#include "TimeManager.hpp"
#include "AssetManager.hpp"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "AquaticRPG");

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e))
            if (e.type == sf::Event::Closed) window.close();

        Time::update();

        window.clear();
        window.setView(window.getDefaultView());
        window.display();
    }
}