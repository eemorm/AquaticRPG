#pragma once

#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "TilePalette.hpp"
#include "Tileset.hpp"



class Editor
{
private:

    Map map;

    Tileset tileset;

    TilePalette palette;

    bool erasing = false;


    std::string mapPath;



    sf::RenderWindow& window;


    sf::View camera;

    sf::View uiView;

    sf::Font uiFont;
    sf::Text layerText;


    Map::Layer currentLayer =
        Map::Layer::Ground;



    int selectedTile = 1;



    bool gridEnabled = true;

    bool painting = false;

    bool draggingCamera = false;

    sf::Vector2i lastMousePosition;

    float zoomLevel = 1.f;



    void paintTile(
        int x,
        int y
    );


    void eraseTile(
        int x,
        int y
    );

    void drawLayerText();

    void drawLayer(
        Map::Layer layer
    );


    void drawGrid();


    void drawPalette();



public:


    Editor(
        sf::RenderWindow& window,
        int width,
        int height,
        const std::string& path
    );



    void handleEvent(
        sf::Event& event
    );


    void update();


    void draw();


    void save();

};