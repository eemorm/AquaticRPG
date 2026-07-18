#pragma once

#include <SFML/Graphics.hpp>

#include "GameMap.hpp"
#include "TileDatabase.hpp"

class MapRenderer
{
    public:
        void draw(
            sf::RenderWindow& window,
            const GameMap& map,
            TileDatabase& tiles
        )
        {
            drawLayer(
                window,
                map,
                tiles,
                GameMap::Layer::Ground
            );

            drawLayer(
                window,
                map,
                tiles,
                GameMap::Layer::Objects
            );

        }
    private:
        void drawLayer(
            sf::RenderWindow& window,
            const GameMap& map,
            TileDatabase& tiles,
            GameMap::Layer layer
        )
        {
            sf::Sprite sprite;

            for(int y = 0;
                y < map.getHeight();
                y++)
            {
                for(int x = 0;
                    x < map.getWidth();
                    x++)
                {
                    int id =
                        map.getTile(
                            x,
                            y,
                            layer
                        );

                    if(id == 0)
                        continue;

                    sprite.setTexture(
                        tiles.getTexture(id)
                    );

                    float size =
                        static_cast<float>(
                            map.getTileSize()
                        );


                    sprite.setOrigin(
                        size / 2.f,
                        size / 2.f
                    );


                    sprite.setPosition(
                        x * size + size / 2.f,
                        y * size + size / 2.f
                    );


                    sprite.setRotation(
                        map.getRotation(
                            x,
                            y,
                            layer
                        )
                    );
                    window.draw(sprite);
                }
            }
        }
};