//#pragma once
//#include <SFML/Graphics.hpp>
//#include "Entity.h"
//template <typename ShapeType>
//class Entity {
//public:
//    ShapeType shape;
//
//    Entity(const ShapeType& s) : shape(s) {}
//
//    virtual ~Entity() = default;
//
//    virtual void update(float speed) = 0; // déplacement propre à chaque entité
//
//    void move(const sf::Vector2f& offset) {
//        shape.move(offset);
//    }
//
//    sf::Vector2f getPosition() const {
//        return shape.getPosition();
//    }
//
//    void setPosition(const sf::Vector2f& pos) {
//        shape.setPosition(pos);
//    }
//
//    sf::FloatRect getBounds() const {
//        return shape.getGlobalBounds();
//    }
//
//    void draw(sf::RenderWindow& window) {
//        window.draw(shape);
//    }
//};
//
//
