#pragma once

#include <SFML/Graphics.hpp>
#include "InputManager.hpp"
#include "CollisionManager.hpp"

class MovementComponent
{
    private:
        float speed = 100.f;
    public:
        MovementComponent() {}

        void update(sf::Vector2f& pos, float dt)
        {
            sf::Vector2f direction(0.f, 0.f);

            if(Input::down("up"))
                direction.y--;
            if(Input::down("down"))
                direction.y++;
            if(Input::down("left"))
                direction.x--;
            if(Input::down("right"))
                direction.x++;

            if (direction.x != 0.f || direction.y != 0.f)
                direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (Collision::canMove({pos.x + direction.x * speed * dt, pos.y}))
            {
                pos.x += direction.x * speed * dt;
            }
            if (Collision::canMove({pos.x, pos.y + direction.y * speed * dt}))
            {
                pos.y += direction.y * speed * dt;
            }
        }
};