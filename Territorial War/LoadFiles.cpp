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

//sf::Texture LoadFiles::loadPartOfTexture(std::string path, sf::IntRect rect)
//{
//	sf::Texture texture;
//	if (!texture.loadFromFile(path, rect))
//	{
//		std::cout << "texture non chargee" << std::endl;
//	}
//	return texture;
//}

sf::Sprite LoadFiles::createSprite(sf::IntRect& rect, sf::Texture& texture )
{
	return sf::Sprite (texture, rect);

}