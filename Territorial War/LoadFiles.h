#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <optional>

class LoadFiles
{
public:
	static sf::Texture loadTexture(std::string path);
	//static sf::Texture loadPartOfTexture(std::string path, sf::IntRect rect);
	static sf::Sprite createSprite(const sf::IntRect& rect, sf::Texture& texture);
};

