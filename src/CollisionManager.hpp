#pragma once

#include <SFML/Graphics.hpp>
#include "GameMap.hpp"

namespace Collision
{
    inline GameMap* map;

    inline bool canMove(sf::Vector2f position)
    {
        int tileX = position.x / map->getTileSize();
        int tileY = position.y / map->getTileSize();

        return !map->isBlocked(tileX, tileY);
    }
}