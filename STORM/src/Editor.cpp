#include "Editor.hpp"

#include <iostream>
#include <filesystem>



Editor::Editor(
    sf::RenderWindow& window,
    int width,
    int height,
    const std::string& path
)
:
map(width,height,16),
window(window),
mapPath(path)
{

    tileset.load(
        "../tiles.json"
    );

    palette.load(
        tileset
    );

    camera.setSize(
        window.getDefaultView().getSize()
    );


    camera.setCenter(
        camera.getSize().x / 2.f,
        camera.getSize().y / 2.f
    );


    uiView =
        window.getDefaultView();

    if(uiFont.loadFromFile("../assets/fonts/sharetech.ttf"))
    {
        layerText.setFont(uiFont);
    }

    layerText.setCharacterSize(20);
    layerText.setFillColor(sf::Color::White);
    layerText.setPosition(1125.f, 10.f);


    palette.load(
        tileset
    );




    if(std::filesystem::exists(mapPath))
    {
        if(map.load(mapPath))
        {
            std::cout
                << "Loaded "
                << mapPath
                << "\n";
        }
        else
        {
            std::cout
                << "Failed loading map\n";
        }
    }
    else
    {
        std::cout
            << "Map does not exist\n";
    }
}







void Editor::paintTile(
    int x,
    int y
)
{
    selectedTile =
        palette.getSelected();


    map.setTile(
        x,
        y,
        selectedTile,
        currentLayer
    );


    if(currentLayer != Map::Layer::Collision)
    {
        map.setRotation(
            x,
            y,
            selectedRotation,
            currentLayer
        );
    }
}

void Editor::eraseTile(
    int x,
    int y
)
{
    map.setTile(
        x,
        y,
        0,
        currentLayer
    );
}








void Editor::handleEvent(
    sf::Event& event
)
{

    if(event.type == sf::Event::MouseButtonPressed)
    {

        if(event.mouseButton.button == sf::Mouse::Left)
        {
            painting = true;
            erasing = false;
        }


        if(event.mouseButton.button == sf::Mouse::Right)
        {
            painting = true;
            erasing = true;
        }


        sf::Vector2i mouse =
            sf::Mouse::getPosition(window);


        if(mouse.x < 220)
        {
            palette.handleClick(mouse);
            return;
        }
    }



    if(event.type == sf::Event::MouseButtonReleased)
    {
        painting = false;
    }






    if(event.type ==
       sf::Event::KeyPressed)
    {


        if(event.key.code ==
           sf::Keyboard::G)
        {
            currentLayer =
                Map::Layer::Ground;
        }


        if(event.key.code ==
           sf::Keyboard::O)
        {
            currentLayer =
                Map::Layer::Objects;
        }


        if(event.key.code ==
           sf::Keyboard::C)
        {
            currentLayer =
                Map::Layer::Collision;
        }




        if(event.key.code ==
           sf::Keyboard::Tab)
        {
            gridEnabled =
                !gridEnabled;
        }





        if(event.key.control &&
           event.key.code ==
           sf::Keyboard::S)
        {
            save();
        }


        if(event.key.code == sf::Keyboard::R)
        {
            selectedRotation += 90;

            if(selectedRotation >= 360)
                selectedRotation = 0;

            std::cout
                << "Rotation: "
                << selectedRotation
                << "\n";
        }


        if(event.key.code ==
           sf::Keyboard::Up)
            camera.move(0,-16);


        if(event.key.code ==
           sf::Keyboard::Down)
            camera.move(0,16);


        if(event.key.code ==
           sf::Keyboard::Left)
            camera.move(-16,0);


        if(event.key.code ==
           sf::Keyboard::Right)
            camera.move(16,0);

    }

    // Middle mouse camera dragging
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Middle)
        {
            draggingCamera = true;

            lastMousePosition =
                sf::Mouse::getPosition(window);
        }
    }


    if(event.type == sf::Event::MouseButtonReleased)
    {
        if(event.mouseButton.button == sf::Mouse::Middle)
        {
            draggingCamera = false;
        }
    }

    if(event.type == sf::Event::MouseWheelScrolled)
    {

        if(event.mouseWheelScroll.delta > 0)
        {
            camera.zoom(0.9f);
            zoomLevel *= 0.9f;
        }


        if(event.mouseWheelScroll.delta < 0)
        {
            camera.zoom(1.1f);
            zoomLevel *= 1.1f;
        }

    }
}









void Editor::update()
{
    if(draggingCamera)
    {

        sf::Vector2i mouse =
            sf::Mouse::getPosition(window);


        sf::Vector2i delta =
            lastMousePosition - mouse;


        camera.move(
            static_cast<float>(delta.x),
            static_cast<float>(delta.y)
        );


        lastMousePosition = mouse;
    }

    if(painting)
    {

        sf::Vector2i mouse =
            sf::Mouse::getPosition(window);



        sf::Vector2f world =
            window.mapPixelToCoords(
                mouse,
                camera
            );



        int x =
            world.x / map.getTileSize();


        int y =
            world.y / map.getTileSize();



        if(erasing)
            eraseTile(x,y);
        else
            paintTile(x,y);
    }
}




void Editor::drawLayerText()
{
    std::string name;


    switch(currentLayer)
    {
        case Map::Layer::Ground:
            name = "Ground";
            break;

        case Map::Layer::Objects:
            name = "Objects";
            break;

        case Map::Layer::Collision:
            name = "Collision";
            break;
    }


    layerText.setString(
        "Layer: " + name +
        "\nRotation: " +
        std::to_string(selectedRotation)
    );


    window.draw(layerText);
}




void Editor::drawLayer(
    Map::Layer layer
)
{

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



            if(layer == Map::Layer::Collision)
            {
                sf::RectangleShape collision;

                collision.setSize(
                    sf::Vector2f(
                        map.getTileSize(),
                        map.getTileSize()
                    )
                );

                collision.setPosition(
                    x * map.getTileSize(),
                    y * map.getTileSize()
                );

                collision.setFillColor(
                    sf::Color(255,0,0,100)
                );

                window.draw(collision);

                continue;
            }


            // Everything below is ONLY normal tiles

            sf::Sprite sprite;


            const sf::Texture* texture =
                tileset.getTexture(id);

            if(texture == nullptr)
                continue;


            sprite.setTexture(
                *texture
            );


            float tileSize =
                static_cast<float>(
                    map.getTileSize()
                );


            sprite.setOrigin(
                tileSize / 2.f,
                tileSize / 2.f
            );


            sprite.setPosition(
                x * tileSize + tileSize / 2.f,
                y * tileSize + tileSize / 2.f
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









void Editor::drawGrid()
{

    sf::VertexArray lines(
        sf::Lines
    );


    float size =
        map.getTileSize();

    sf::Color gridColor(
        255,
        255,
        255,
        50
    );

    for(int x=0;
        x<=map.getWidth();
        x++)
    {

        lines.append(
            sf::Vertex(
                sf::Vector2f(
                    x*size,
                    0
                ),
                gridColor
            )
        );


        lines.append(
            sf::Vertex(
                sf::Vector2f(
                    x*size,
                    map.getHeight()*size
                ),
                gridColor
            )
        );
    }



    for(int y=0;
        y<=map.getHeight();
        y++)
    {

        lines.append(
            sf::Vertex(
                sf::Vector2f(
                    0,
                    y*size
                ),
                gridColor
            )
        );


        lines.append(
            sf::Vertex(
                sf::Vector2f(
                    map.getWidth()*size,
                    y*size
                ),
                gridColor
            )
        );
    }



    window.draw(lines);
}









void Editor::drawPalette()
{
    palette.draw(window);
}









void Editor::draw()
{

    window.setView(
        camera
    );


    drawLayer(
        Map::Layer::Ground
    );


    drawLayer(
        Map::Layer::Objects
    );


    drawLayer(
        Map::Layer::Collision
    );



    if(gridEnabled)
        drawGrid();




    window.setView(
        uiView
    );


    drawPalette();

    drawLayerText();
}









void Editor::save()
{

    if(map.save(mapPath))
    {
        std::cout
            << "Saved map\n";
    }

}