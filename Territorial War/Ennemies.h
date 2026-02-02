#pragma once
#include "Entity.h"

class Ennemies: public Entity<sf::RectangleShape> {
public:
    Ennemies() : Entity(sf::RectangleShape({ 50.f, 50.f })){}

    void update(float speed) override;

};


