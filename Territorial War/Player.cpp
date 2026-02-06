#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

Player::Player()
    : Entity(sf::CircleShape(25.f)) 
{
    getShape().setFillColor(sf::Color::Blue);
}

void Player::update(float dt)
{
    sf::Vector2f moveVec(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) moveVec.y -= 200.f * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) moveVec.y += 200.f * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) moveVec.x -= 200.f * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) moveVec.x += 200.f * dt;

    move(moveVec);

    // block les sortir de la fenêtre en (800x600)
    auto pos = getPosition();
    float radius = getShape().getRadius();

    pos.x = std::clamp(pos.x, 0.f, 800.f - radius * 2.f);
    pos.y = std::clamp(pos.y, 0.f, 600.f - radius * 2.f);

    setPosition(pos);
}
