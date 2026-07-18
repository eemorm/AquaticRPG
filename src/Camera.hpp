#pragma once

// SFML
#include <SFML/Graphics.hpp>

class Camera 
{
    private:
        sf::View view; // view of the camera
    public:
        Camera(sf::Vector2f size) { view.setSize(size); view.setCenter(size.x / 2.f, size.y / 2.f); }

        sf::View& getView() { return view; } // get the camera's view

        void follow(const sf::Vector2f& targetPos) { view.setCenter(targetPos); } // update the camera to follow a specific object
        void move(sf::Vector2f amount) { view.move(amount); } // move the camera by a certain amount
        void zoom(float amount) { view.zoom(amount); } // zoom in or out of the camera
        void apply(sf::RenderWindow& window) { window.setView(view); } // apply the camera to the window
};
