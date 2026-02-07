#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Rocks
{
public:
    Rocks();

    sf::Texture rockTex;
    std::vector<sf::Sprite> rocks;
};