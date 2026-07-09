#pragma once

// SFML
#include <SFML/System.hpp>

namespace Time
{
    // PUBLIC
    inline float delta = 0.f; // delta time - time since last frame
    inline float elapsed = 0.f; // total clock runtime
    inline int fps; // fps
    inline float fpsUpdateThreshold = 1.f; // how long between fps updates
    inline float timeScale = 1.f; // how fast/slow time goes, can be scaled faster or slower for effect

    inline sf::Clock clock; // time clock
    inline float fpsTimer = 1.f; // timer to update fps only after certain amounts of time
    inline int frameCount = 0; // amount of frames since last fps counter update
    inline std::unordered_map<std::string, float> timers; // timers that can keep track of specific events

    inline void update() // method to update time per frame
    {
        delta = clock.restart().asSeconds() * timeScale; // get delta time by restarting clock per frame
        elapsed += delta; // add delta time to elapsed total time

        frameCount++; // update frame count
        fpsTimer += delta; // increase fps timer

        if (fpsTimer >= fpsUpdateThreshold) // once fps timer reaches its threshold
        {
            fps = frameCount; // keep track of fps by saving it in a variable
            frameCount = 0; // reset fps to track again
            fpsTimer -= fpsUpdateThreshold; // reset fpsTimer
        }

        for (auto& [name, time] : timers) // increment timers
            time += delta;
    }
    inline void resetTimer(const std::string& name) { timers[name] = 0.f; } // reset specific timer
    inline float getTimer(const std::string& name) // get an active timer, and if not active, begin it
    {
        if (!timers.contains(name)) timers[name] = 0.f; // start timer if not active
        return timers[name]; // get timer from name
    }
}