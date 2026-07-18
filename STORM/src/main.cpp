#include <iostream>
#include <vector>

#include "Editor.hpp"
#include "MapManager.hpp"


int main()
{

    std::cout
        << "STORM RPG Map Editor\n\n";


    std::cout
        << "1. New Map\n"
        << "2. Load Map\n"
        << "Choice: ";


    int choice;
    std::cin >> choice;



    std::string mapName;



    if(choice == 1)
    {

        int width;
        int height;


        std::cout
            << "Map name: ";

        std::cin
            >> mapName;


        std::cout
            << "Width: ";

        std::cin
            >> width;


        std::cout
            << "Height: ";

        std::cin
            >> height;



        if(!MapManager::createMap(
            mapName,
            width,
            height
        ))
        {
            std::cout
                << "Failed creating map\n";

            return 1;
        }


        std::cout
            << "Created map\n";

    }



    else if(choice == 2)
    {

        auto maps =
            MapManager::getMaps();



        if(maps.empty())
        {
            std::cout
                << "No maps found\n";

            return 0;
        }



        std::cout
            << "\nMaps:\n";


        for(int i = 0;
            i < maps.size();
            i++)
        {
            std::cout
                << i+1
                << ". "
                << maps[i]
                << "\n";
        }



        int selected;

        std::cin
            >> selected;


        mapName =
            maps[selected-1];

    }



    sf::RenderWindow window(
        sf::VideoMode(1280,720),
        "STORM Editor"
    );


    Editor editor(
        window,
        50,
        50,
        "../maps/" + mapName + ".json"
    );



    while(window.isOpen())
    {

        sf::Event event;


        while(window.pollEvent(event))
        {

            if(event.type ==
               sf::Event::Closed)
            {
                window.close();
            }


            editor.handleEvent(event);
        }



        window.clear(
            sf::Color(40,40,40)
        );


        editor.update();


        editor.draw();


        window.display();

    }


    return 0;
}