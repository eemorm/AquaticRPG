#pragma once
#include "Types.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <unordered_set>

struct Transform 
{
    sf::Vector2f pos;
    sf::Vector2f vel;
};
struct PlayerControl 
{
    float speed = 200.f;
};
struct Sprite 
{
    sf::Sprite sprite;
};
struct Health 
{
    int hp;
    int max;
};

struct Player {};
struct Enemy {};

struct World 
{
    Entity next = 1;

    std::unordered_map<Entity, Transform> transform;
    std::unordered_map<Entity, PlayerControl> playerControl;
    std::unordered_map<Entity, Sprite> sprite;
    std::unordered_map<Entity, Health> health;

    std::unordered_set<Entity> players;
    std::unordered_set<Entity> enemies;

    Entity create() 
    {
        return next++;
    }
    void destroy(Entity e) 
    {
        transform.erase(e);
        sprite.erase(e);
        health.erase(e);
        players.erase(e);
        enemies.erase(e);
    }
};