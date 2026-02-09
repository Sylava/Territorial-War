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
#include <SFML/Graphics.hpp>
#include "Map.h"

class Player
{
public:
    Player();
    Player(sf::RenderWindow* inWindow, const Map* map);

    void update(const float dt);
    void attackAnimation(const float dt);
    void runAnimation(const float dt);
    void idleAnimation(const float dt);
    void move(const sf::Vector2f& move, const Map* map);
    void draw();

    sf::Vector2f position;
    sf::FloatRect hitbox;
    float speed = 400.f;
    float invunerability = 1.f;
    bool isAttacking = false;
    bool isMoving = false;
    int hp = 5;
    bool animMirror = true;
    int attackIndex = 0;
    float attackAnimTime = 0.08f;
    sf::Texture attackTex;
    std::optional<sf::Sprite> playerSprite;
    sf::CircleShape attackArea;

private:
    void moveOnAxis(float& pos, float& hitboxPos, float delta, float min, float max, const Map* map);

    sf::RenderWindow* window;
    sf::Texture idleTex;
    sf::Texture runTex;
    bool idleReverse = false;
    bool runReverse = false;
    int runIndex = 0;
    int idleIndex = 0;
    float runAnimTime = 0.08f;
    float idleAnimTime = 0.08f;
};
