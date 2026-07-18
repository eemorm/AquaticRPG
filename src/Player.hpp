#pragma once

#include <SFML/Graphics.hpp>
#include "MovementComponent.hpp"

class Player
{
    private:
        sf::Sprite sprite;
        sf::Vector2f position;
        MovementComponent movement;
    public:
        Player(sf::Texture& texture) : sprite(texture) {}

        void update(float dt)
        {
            movement.update(position, dt);
            sprite.setPosition(position);
        }
        void draw(sf::RenderWindow& window)
        {
            window.draw(sprite);
        }

        sf::Sprite& getSprite() { return sprite; }
        void setPosition(sf::Vector2f pos) { position = pos; sprite.setPosition(position); }
};