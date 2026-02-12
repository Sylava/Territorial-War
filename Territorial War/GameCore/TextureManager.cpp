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

// delete les textures
void TextureManager::clear()
{
	for (auto pair : textures)
	{
		delete pair.second;
	}
	textures.clear();
}

// charge une texture
sf::Texture* TextureManager::loadTexture(std::string const& path)
{
	if (instance == nullptr)
		return nullptr;
	// On vérifie si la texture à déjà été chargée
	auto ret = instance->textures.find(path);
	if (ret != instance->textures.end())
	{
		return ret->second; // on retourne la texture chargée si c'est le cas
	}
	// Sinon on charge la texture
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(path))
	{
		std::cout << "texture non chargee" << std::endl;
		delete texture;
		return nullptr;
	}
	// On sauvegarde la texture
	instance->textures.insert(std::pair{ path, texture });
	return texture;
}