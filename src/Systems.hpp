#pragma once

// SFML
#include <SFML/Window.hpp>

// Custom Includes
#include "World.hpp"

inline void movementSystem(World& w, float dt) 
{
    for (auto& [e, t] : w.transform)
        t.pos += t.vel * dt;
}
inline void playerControlSystem(World& w) 
{
    for (auto& [e, ctrl] : w.playerControl) {
        if (!w.transform.count(e)) continue;

        auto& t = w.transform[e];
        t.vel = {0.f, 0.f};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) t.vel.y -= ctrl.speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) t.vel.y += ctrl.speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) t.vel.x -= ctrl.speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) t.vel.x += ctrl.speed;
    }
}
inline void renderSystem(World& w, sf::RenderWindow& win) 
{
    for (auto& [e, s] : w.sprite) 
    {
        if (!w.transform.count(e)) continue;
        s.sprite.setPosition(w.transform[e].pos);
        win.draw(s.sprite);
    }
}
inline void healthSystem(World& w) 
{
    for (auto& [e, h] : w.health) 
    {
        if (h.hp <= 0)
            w.destroy(e);
    }
}
