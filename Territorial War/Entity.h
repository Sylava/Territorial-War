//#pragma once
//#include <SFML/Graphics.hpp>
//
//template <typename ShapeType>
//class Entity {
//public:
//    ShapeType shape;
//
//    Entity(){}
//    Entity(const ShapeType& s) : shape(s) {}
//
//    virtual ~Entity() = default;
//
//    virtual void update(float dt) = 0; // déplacement propre à chaque entité
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


#pragma once
#include <SFML/Graphics.hpp>

template<typename T>
class Entity
{
public:
    Entity(const T& drawable) : m_drawable(drawable) {}
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;

    void move(const sf::Vector2f& offset) {
        m_drawable.move(offset);
    }

    void setPosition(const sf::Vector2f& pos) {
        m_drawable.setPosition(pos);
    }

    sf::Vector2f getPosition() const {
        return m_drawable.getPosition();
    }

    T& getShape() { return m_drawable; }

protected:
    T m_drawable;
};
