#pragma once
#include "Entity.h"

class Player : public Entity<sf::CircleShape> {
public:
    Player() : Entity(sf::CircleShape(20.f)) {
        shape.setFillColor(sf::Color::Red);
        shape.setPosition({ 400.f, 300.f });
    }

    void update(float speed) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
            move({ 0.f, -speed });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
            move({ 0.f, speed });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
            move({ -speed, 0.f });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
            move({ speed, 0.f });
    }
};
