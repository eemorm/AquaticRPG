#include "MapManager.hpp"

#include <filesystem>
#include <iostream>

#include "Map.hpp"


namespace fs = std::filesystem;



std::vector<std::string>
MapManager::getMaps()
{

    std::vector<std::string> maps;


    fs::create_directory(
        "../maps"
    );


    for(auto& file :
        fs::directory_iterator("../maps"))
    {

        if(file.path().extension() == ".json")
        {
            maps.push_back(
                file.path().stem().string()
            );
        }

    }


    return maps;
}





bool MapManager::createMap(
    const std::string& name,
    int width,
    int height
)
{

    fs::create_directory(
        "../maps"
    );


    Map map(
        width,
        height,
        16
    );


    return map.save(
        "../maps/" + name + ".json"
    );
}