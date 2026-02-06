#pragma once
#include "Entity.h"

class Obstacle : public Entity<sf::RectangleShape>
{
public:
    Obstacle();
    void update(float dt) override {} 
};
