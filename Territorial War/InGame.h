#pragma once
#include <SFML/Graphics.hpp>


class InGame
{
public:
	void init();
	void run(sf::RenderWindow* window);

private:
	sf::Texture landTex;
	sf::Texture bgTex;
	std::vector<sf::Sprite> lands;
	int mapWidth = 3;
	int mapHeight = 3;

	void createFirstRow();
	void createMiddleRows();
	void draw(sf::RenderWindow* window);
};

