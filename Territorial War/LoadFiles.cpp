#include <SFML/Graphics.hpp>
#include "LoadFiles.h"
#include "iostream"

sf::Texture LoadFiles::loadTexture(std::string path)
{
	sf::Texture texture;
	if (!texture.loadFromFile(path))
	{
		std::cout << "texture non chargee" << std::endl;
	}
	return texture;
}

sf::Sprite LoadFiles::createSprite(const sf::IntRect& rect, sf::Texture& texture )
{
	return sf::Sprite (texture, rect);

}