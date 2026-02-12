#include <iostream>
#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager()
{
	if (instance == nullptr)
		instance = this;
}

TextureManager::~TextureManager()
{
	if (instance == this)
		instance = nullptr;
	clear();
}

void TextureManager::clear()
{
	for (auto pair : textures)
	{
		delete pair.second;
	}
}

sf::Texture* TextureManager::loadTexture(std::string const& path)
{
	if (instance == nullptr)
		return nullptr;
	auto ret = instance->textures.find(path);
	if (ret != instance->textures.end())
	{
		return ret->second;
	}
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(path))
	{
		std::cout << "texture non chargee" << std::endl;
		delete texture;
		return nullptr;
	}
	instance->textures.insert(std::pair{ path, texture });
	return texture;
}