#include "TilePalette.hpp"

#include <iostream>



void TilePalette::load(
    Tileset& tileset
)
{

    this->tileset = &tileset;


    tileIDs.clear();


    for(int i = 1;
        i <= tileset.getTileCount();
        i++)
    {
        tileIDs.push_back(i);
    }



    if(!tileIDs.empty())
        selected = tileIDs[0];


    std::cout
        << "Palette loaded "
        << tileIDs.size()
        << " tiles\n";
}






void TilePalette::draw(
    sf::RenderWindow& window
)
{

    int x = 10;
    int y = 10;



    for(int id : tileIDs)
    {

        const sf::Texture* texture =
            tileset->getTexture(id);



        if(texture == nullptr)
            continue;



        sf::Sprite sprite;


        sprite.setTexture(
            *texture
        );



        sprite.setPosition(
            static_cast<float>(x),
            static_cast<float>(y)
        );



        sprite.setScale(
            2.f,
            2.f
        );



        window.draw(sprite);



        if(id == selected)
        {

            sf::RectangleShape outline;


            outline.setSize(
                sf::Vector2f(
                    32.f,
                    32.f
                )
            );


            outline.setPosition(
                static_cast<float>(x),
                static_cast<float>(y)
            );


            outline.setFillColor(
                sf::Color::Transparent
            );


            outline.setOutlineThickness(
                2.f
            );


            outline.setOutlineColor(
                sf::Color::Yellow
            );


            window.draw(outline);
        }



        x += 40;



        if(x > 180)
        {
            x = 10;
            y += 40;
        }
    }
}








void TilePalette::handleClick(
    sf::Vector2i mouse
)
{

    int x = 10;
    int y = 10;



    for(int id : tileIDs)
    {

        sf::FloatRect box(
            static_cast<float>(x),
            static_cast<float>(y),
            32.f,
            32.f
        );



        if(box.contains(
            static_cast<float>(mouse.x),
            static_cast<float>(mouse.y)
        ))
        {

            selected = id;


            std::cout
                << "Selected tile "
                << selected
                << "\n";


            return;
        }



        x += 40;



        if(x > 180)
        {
            x = 10;
            y += 40;
        }
    }
}






int TilePalette::getSelected() const
{
    return selected;
}