#pragma once
#include <SFML/Graphics.hpp>
#include "../Map.h"
#include "Entity.h"

class Player: public Entity
{
public:
    Player(sf::RenderWindow* inWindow, const Map* map);

    void move(const sf::Vector2f& move, const Map* map);

    sf::CircleShape attackArea;

private:
    void moveOnAxis(float& pos, float& hitboxPos, float delta, float min, float max, const Map* map);
    
};
