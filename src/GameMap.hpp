#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class GameMap
{
    public:
        enum class Layer
        {
            Ground,
            Objects,
            Collision
        };
    private:
        int width = 0;
        int height = 0;
        int tileSize = 16;

        std::vector<int> ground;
        std::vector<int> objects;
        std::vector<int> collision;
    public:
        bool load(
            const std::string& path
        )
        {

            std::ifstream file(path);

            if(!file)
            {
                std::cerr
                    << "Could not open map: "
                    << path
                    << "\n";

                return false;
            }

            json j;

            try
            {
                file >> j;
            }

            catch(std::exception& e)
            {
                std::cerr
                    << "JSON error: "
                    << e.what()
                    << "\n";

                return false;
            }

            width =
                j["width"];
            height =
                j["height"];
            tileSize =
                j["tileSize"];
            ground =
                j["layers"]["ground"]
                .get<std::vector<int>>();
            objects =
                j["layers"]["objects"]
                .get<std::vector<int>>();
            collision =
                j["layers"]["collision"]
                .get<std::vector<int>>();

            std::cout
                << "Loaded map "
                << width
                << "x"
                << height
                << "\n";

            return true;
        }

        int getTile(
            int x,
            int y,
            Layer layer
        ) const
        {
            if(x < 0 ||
            y < 0 ||
            x >= width ||
            y >= height)
            {
                return 0;
            }

            int index = y * width + x;

            switch(layer)
            {
                case Layer::Ground:
                    return ground[index];
                case Layer::Objects:
                    return objects[index];
                case Layer::Collision:
                    return collision[index];
            }
            return 0;
        }

        bool isBlocked(
            int x,
            int y
        ) const
        {

            return getTile(
                x,
                y,
                Layer::Collision
            ) != 0;

        }

        int getWidth() const
        {
            return width;
        }

        int getHeight() const
        {
            return height;
        }

        int getTileSize() const
        {
            return tileSize;
        }
};