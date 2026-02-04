//#pragma once
//#include "Entity.h"
//
//
//
//class Player : public Entity<sf::CircleShape> {
//public:
//    Player();
//
//    void update(float speed) override;
//};

class Player {
public:
    sf::RectangleShape shape;
    float speed = 150.f;

    Player() {
        shape.setSize({ 28, 28 });
        shape.setFillColor(sf::Color::Red);
        shape.setPosition({ 50, 50 });
    }

    void update(float dt, const TileMap& map) {
        sf::Vector2f move(0, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) move.y -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) move.y += speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) move.x -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) move.x += speed * dt;

        sf::Vector2f newPos = shape.getPosition() + move;

        // Collision avec les murs
        int tileX = newPos.x / TileMap::TILE_X;
        int tileY = newPos.y / TileMap::TILE_Y;

        if (map.getTile(tileX, tileY) != TileType::Wall)
            shape.setPosition(newPos);
    }
};
