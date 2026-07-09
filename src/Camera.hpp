#pragma once

// SFML
#include <SFML/Graphics.hpp>

class Camera 
{
    private:
        sf::View view; // view of the camera
    public:
        Camera(sf::Vector2f size) { view.setSize(size); }

        sf::View& getView() { return view; } // get the camera's view

        void follow(const sf::Vector2f& targetPos) { view.setCenter(targetPos); } // update the camera to follow a specific object
        void apply(sf::RenderWindow& window) { window.setView(view); } // apply the camera to the window
};
