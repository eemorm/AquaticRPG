#pragma once

#include <vector>
#include <string>

class Map
{
public:

    enum class Layer
    {
        Ground,
        Objects,
        Collision
    };


private:

    int width;
    int height;
    int tileSize;

    std::vector<int> ground;
    std::vector<int> objects;
    std::vector<int> collision;


    std::vector<int>& getLayer(Layer layer);
    const std::vector<int>& getLayer(Layer layer) const;


public:

    Map(int width, int height, int tileSize = 32);


    int getWidth() const;
    int getHeight() const;
    int getTileSize() const;


    int getTile(int x, int y, Layer layer) const;

    void setTile(
        int x,
        int y,
        int tileID,
        Layer layer
    );


    void clear();


    bool save(const std::string& path);

    bool load(const std::string& path);
};