#pragma once
#include "Entity.h"

class Ennemies: public Entity<sf::RectangleShape> {
public:
    Ennemies() : Entity(sf::RectangleShape({ 50.f, 50.f })) {
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition({ 200.f, 150.f });
    }

    void update(float speed) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
            move({ 0.f, -speed });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
            move({ 0.f, speed });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
            move({ -speed, 0.f });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
            move({ speed, 0.f });
    }

};


