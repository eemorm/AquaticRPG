#include "Map.hpp"

#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;



Map::Map(int width, int height, int tileSize)
    :
    width(width),
    height(height),
    tileSize(tileSize)
{
    int size = width * height;

    ground.resize(size, 0);
    groundRotation.resize(size, 0);
    objects.resize(size, 0);
    objectsRotation.resize(size, 0);
    collision.resize(size, 0);
}



int Map::getWidth() const
{
    return width;
}


int Map::getHeight() const
{
    return height;
}


int Map::getTileSize() const
{
    return tileSize;
}



std::vector<int>& Map::getLayer(Layer layer)
{
    switch(layer)
    {
        case Layer::Ground:
            return ground;

        case Layer::Objects:
            return objects;

        case Layer::Collision:
            return collision;
    }

    return ground;
}



const std::vector<int>& Map::getLayer(Layer layer) const
{
    switch(layer)
    {
        case Layer::Ground:
            return ground;

        case Layer::Objects:
            return objects;

        case Layer::Collision:
            return collision;
    }

    return ground;
}

std::vector<int>& Map::getRotationLayer(
    Layer layer
)
{
    switch(layer)
    {
        case Layer::Ground:
            return groundRotation;

        case Layer::Objects:
            return objectsRotation;

        case Layer::Collision:
            return groundRotation;
    }

    return groundRotation;
}



const std::vector<int>& Map::getRotationLayer(
    Layer layer
) const
{
    switch(layer)
    {
        case Layer::Ground:
            return groundRotation;

        case Layer::Objects:
            return objectsRotation;

        case Layer::Collision:
            return groundRotation;
    }

    return groundRotation;
}

int Map::getTile(int x, int y, Layer layer) const
{
    if(x < 0 || y < 0 ||
       x >= width ||
       y >= height)
        return 0;


    const auto& tiles = getLayer(layer);

    return tiles[y * width + x];
}

int Map::getRotation(
    int x,
    int y,
    Layer layer
) const
{
    if(x < 0 || y < 0 ||
       x >= width ||
       y >= height)
    {
        return 0;
    }


    const auto& rotations =
        getRotationLayer(layer);


    return rotations[y * width + x];
}

void Map::setTile(
    int x,
    int y,
    int tileID,
    Layer layer
)
{
    if(x < 0 || y < 0 ||
       x >= width ||
       y >= height)
        return;


    auto& tiles = getLayer(layer);

    tiles[y * width + x] = tileID;
}

void Map::setRotation(
    int x,
    int y,
    int rotation,
    Layer layer
)
{
    if(x < 0 || y < 0 ||
       x >= width ||
       y >= height)
    {
        return;
    }


    auto& rotations =
        getRotationLayer(layer);


    rotations[y * width + x] =
        rotation;
}

void Map::clear()
{
    std::fill(
        ground.begin(),
        ground.end(),
        0
    );

    std::fill(
        objects.begin(),
        objects.end(),
        0
    );

    std::fill(
        collision.begin(),
        collision.end(),
        0
    );
}



bool Map::save(const std::string& path)
{
    json j;


    j["width"] = width;
    j["height"] = height;
    j["tileSize"] = tileSize;


    j["layers"]["ground"] = ground;
    j["layers"]["groundRotation"] = groundRotation;
    j["layers"]["objects"] = objects;
    j["layers"]["objectsRotation"] = objectsRotation;
    j["layers"]["collision"] = collision;



    std::ofstream file(path);

    if(!file)
    {
        std::cerr
            << "Could not save map\n";

        return false;
    }


    file << j.dump(4);


    return true;
}



bool Map::load(const std::string& path)
{
    std::ifstream file(path);


    if(!file)
    {
        return false;
    }


    json j;
    file >> j;


    width = j["width"];
    height = j["height"];
    tileSize = j["tileSize"];


    ground =
        j["layers"]["ground"]
        .get<std::vector<int>>();

    groundRotation =
        j["layers"]["groundRotation"]
        .get<std::vector<int>>();

    objects =
        j["layers"]["objects"]
        .get<std::vector<int>>();

    objectsRotation =
        j["layers"]["objectsRotation"]
        .get<std::vector<int>>();

    collision =
        j["layers"]["collision"]
        .get<std::vector<int>>();



    return true;
}