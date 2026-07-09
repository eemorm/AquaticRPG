#pragma once

// SFML
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// Standard Libraries
#include <unordered_map>
#include <string>

namespace Input
{
    struct KeyState // whether a key is pressed, held down, or released
    {
        bool down = false;
        bool pressed = false;
        bool released = false;
    };

    inline std::unordered_map<std::string, KeyState> keyStates; // states of keys, whether they are pressed, held, or released
    inline std::unordered_map<std::string, sf::Keyboard::Key> keyBindings; // binding of simple strings to SFML keys

    inline void update() // update key state
    {
        for (auto& [action, key] : keyBindings) // for each key
        {
            // get the proper state of the key
            bool currentlyDown = sf::Keyboard::isKeyPressed(key);

            KeyState& state = keyStates[action];
            state.pressed  = currentlyDown && !state.down;
            state.released = !currentlyDown && state.down;
            state.down     = currentlyDown;
        }
    }
    inline void bind(const std::string& action, sf::Keyboard::Key key) // set a specific string to an SFML key
    {
        keyBindings[action] = key;

        if (keyStates.find(action) == keyStates.end())
            keyStates[action] = KeyState();
    }
    // specific state grabbers for keys
    inline bool pressed(const std::string& action) { return keyStates[action].pressed; }
    inline bool released(const std::string& action) { return keyStates[action].released; }
    inline bool down(const std::string& action) { return keyStates[action].down; }
}