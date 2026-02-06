#include "Obstacle.h"
#include <random>

Obstacle::Obstacle()
    : Entity(sf::RectangleShape({ 60.f, 60.f }))
{
    getShape().setFillColor(sf::Color(120, 120, 120));

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> distX(0, 740);
    std::uniform_int_distribution<int> distY(0, 540);

    setPosition({ (float)distX(gen), (float)distY(gen) });
}
