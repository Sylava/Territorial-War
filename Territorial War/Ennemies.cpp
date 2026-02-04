//#include "Ennemies.h"
//
//Ennemies::Ennemies() : Entity(sf::RectangleShape({ 50.f, 50.f }))
//{
//    shape.setFillColor(sf::Color::Blue);
//    shape.setPosition({ 200.f, 150.f });
//}
//
//void Ennemies::update(float speed)
//{
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
//        move({ 0.f, -speed });
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
//        move({ 0.f, speed });
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
//        move({ -speed, 0.f });
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
//        move({ speed, 0.f });
//}