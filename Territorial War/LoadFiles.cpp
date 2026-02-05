#include "LoadFiles.h"
#include "iostream"

sf::Texture LoadFiles::loadTexture(std::string path)
{
	sf::Texture texture;
	if (!texture.loadFromFile("path"))
	{
		std::cout << "error loading texture" << std::endl;
	}
}