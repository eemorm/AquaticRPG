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
        std::vector<int> groundRotation;
        std::vector<int> objects;
        std::vector<int> objectsRotation;
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


            int size = width * height;


            // Load rotations if they exist
            if(j["layers"].contains("groundRotation"))
            {
                groundRotation =
                    j["layers"]["groundRotation"]
                    .get<std::vector<int>>();
            }
            else
            {
                groundRotation.resize(size, 0);
            }


            if(j["layers"].contains("objectsRotation"))
            {
                objectsRotation =
                    j["layers"]["objectsRotation"]
                    .get<std::vector<int>>();
            }
            else
            {
                objectsRotation.resize(size, 0);
            }

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

        int getRotation(
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
                    return groundRotation[index];

                case Layer::Objects:
                    return objectsRotation[index];

                case Layer::Collision:
                    return 0;
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