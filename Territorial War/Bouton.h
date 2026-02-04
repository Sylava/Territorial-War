#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& textString) {
        shape.setPosition(pos);
        shape.setSize(size);
        shape.setFillColor(sf::Color(100, 100, 100));

        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setString(textString);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2, bounds.height / 2);
        text.setPosition(pos + size / 2.f);
    }

    bool isHovered(const sf::Vector2i& mousePos) const {
        return shape.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y);
    }

    bool isClicked(const sf::Event& event, const sf::Vector2i& mousePos) const {
        return event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left &&
            isHovered(mousePos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
};
