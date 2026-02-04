#pragma once
#include <SFML/Graphics.hpp>

template <typename T>
class Scene {
public:
    virtual ~Scene() = default;

    virtual void handleEvent(const sf::Event& event, T& app) = 0;
    virtual void update(T& app, float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};
