#pragma once

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Custom Includes
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

/*
    AssetManager.hpp

    -AssetLoader and manager
    -Applicable to difference contexts
    -Built for SFML but can be modified for anything
*/

namespace Assets // assets namespace to keep 
{
    // maps to modularly store assets
    inline std::unordered_map<std::string, sf::Texture> textures;
    inline std::unordered_map<std::string, sf::Font> fonts;
    inline std::unordered_map<std::string, std::unique_ptr<sf::Shader>> shaders;
    inline std::unordered_map<std::string, sf::SoundBuffer> sounds;
    // reference to current music because only a single one needs to be streamed from disk
    inline std::unique_ptr<sf::Music> currentMusic;


    // GET ASSET FROM MAP METHODS
    /*
    
    // FORMAT

    sf::(Asset)& get(Asset)(std::string path) // get or load an asset from the AssetManager
    {
        // if asset path not mapped in the appropriate map
            // load the asset and move it into the map, else error
        // return the asset from the map, now that it is in the map or was already
    }

    // EXCEPTION
    // shaders must be used with unique ptr because they cannot be moved

    */

    sf::Texture& getTexture(std::string path)
    {
        if (!textures.contains(path))
        {
            sf::Texture texture;
            if (!texture.loadFromFile(path))
            {
                std::cout << "Error - texture not loaded at " + path << std::endl;
            }

            textures[path] = std::move(texture);
        }
        return textures.at(path);
    }
    sf::Font& getFont(std::string path)
    {
        if (!fonts.contains(path))
        {
            sf::Font font;
            if (!font.loadFromFile(path))
            {
                std::cout << "Error - font not loaded at " + path << std::endl;
            }

            fonts[path] = std::move(font);
        }
        return fonts.at(path);
    }
    sf::Shader& getShader(std::string path)
    {
        if (!shaders.contains(path))
        {
            auto shader = std::make_unique<sf::Shader>();
            if (!shader->loadFromFile(path, sf::Shader::Fragment))
            {
                std::cout << "Error - shader not loaded at " + path << std::endl;
            }

            shaders[path] = std::move(shader);
        }
        return *shaders.at(path);
    }
    sf::SoundBuffer& getSound(std::string path)
    {
        if (!sounds.contains(path))
        {
            sf::SoundBuffer sound;
            if (!sound.loadFromFile(path))
            {
                std::cout << "Error - sound not loaded at " + path << std::endl;
            }

            sounds[path] = std::move(sound);
        }
        return sounds.at(path);
    }


    // music streaming and stopping
    bool playMusic(std::string path, bool loop = true, float volume = 100.f) // stream and play music with settings passed in
    {
        if (currentMusic) // if music is playing
            currentMusic->stop(); // stop it

        currentMusic = std::make_unique<sf::Music>(); // make new current music
        
        if (!currentMusic->openFromFile(path)) // attempt to open the music at the path that is passed in 
        {
            currentMusic.reset();
            return false;
        }

        // set loop and volume if chosen
        currentMusic->setLoop(loop);
        currentMusic->setVolume(volume);
        // play music from streamed currentMusic
        currentMusic->play();

        return true;
    }
    void stopMusic() // stop playing the current music
    {
        if (currentMusic) // if there is music to stop
            currentMusic->stop(); // stop it
    }
}