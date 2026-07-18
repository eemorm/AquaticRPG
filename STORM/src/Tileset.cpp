#include "Tileset.hpp"

#include <filesystem>
#include <iostream>
#include <vector>
#include <algorithm>


bool Tileset::load(
    const std::string& folder
)
{

    textures.clear();


    std::vector<std::filesystem::path> files;


    for(auto& file :
        std::filesystem::directory_iterator(folder))
    {

        if(file.path().extension() == ".png")
        {
            files.push_back(file.path());
        }
    }


    std::sort(
        files.begin(),
        files.end()
    );



    int id = 1;


    for(auto& path : files)
    {

        sf::Texture texture;


        if(!texture.loadFromFile(
            path.string()
        ))
        {
            std::cout
                << "Failed: "
                << path
                << "\n";

            continue;
        }


        texture.setSmooth(false);



        textures[id] =
            std::move(texture);



        std::cout
            << id
            << " = "
            << path.filename()
            << "\n";


        id++;
    }



    return !textures.empty();
}




const sf::Texture* Tileset::getTexture(
    int id
) const
{

    auto it =
        textures.find(id);


    if(it == textures.end())
        return nullptr;


    return &it->second;
}





bool Tileset::hasTile(
    int id
) const
{
    return textures.count(id);
}





int Tileset::getTileCount() const
{
    return textures.size();
}