#pragma once

#include <string>
#include <vector>


class MapManager
{

public:

    static std::vector<std::string> getMaps();

    static bool createMap(
        const std::string& name,
        int width,
        int height
    );

};