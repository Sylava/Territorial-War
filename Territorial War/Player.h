//#pragma once
//#include "Entity.h"
//
//class Player : public Entity<sf::CircleShape> {
//public:
//    Player() : Entity(sf::CircleShape(20.f)) {
//        shape.setFillColor(sf::Color::Red);
//        shape.setPosition({ 400.f, 300.f });
//    }
//
//    void update(float dt) override {
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
//            move({ 0.f, -speed * dt });
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
//            move({ 0.f, speed * dt });
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
//            move({ -speed * dt, 0.f });
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
//            move({ speed * dt, 0.f });
//    }
//
//private:
//    float speed = 220.f;
//    int pv = 5;
//};

#pragma once
#include "Entity.h"

class Player : public Entity<sf::CircleShape>
{
public:
    Player();
    void update(float dt) override;
};
