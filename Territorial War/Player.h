#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player {
public:
    Player(sf::RenderWindow* inWindow);

    void update(float dt);
    void move(const sf::Vector2f& offset);
    void draw();

    sf::Vector2f position;
    float speed = 180.f;
    bool isMoving = false;
    bool wasMoving = false;
    bool direction = true;

private:
    sf::RenderWindow* window;
    sf::Texture idleTex;
    sf::Texture runTex;
    std::optional<sf::Sprite> playerSprite;
    int pv = 5;
    int idleIndex = 0;
    bool idleReverse = false;
    int runIndex = 0;
    bool runReverse = false;
    float animTime = 0.08f;
};
