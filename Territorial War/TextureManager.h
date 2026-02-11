#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void clear();
	static sf::Texture* loadTexture(std::string const& path);

private:
	std::map<std::string, sf::Texture*> textures;
	static TextureManager* instance;
};

