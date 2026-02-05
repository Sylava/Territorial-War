#pragma once
#include <SFML/Graphics.hpp>
#include <optional>


class InGame
{
public:
	void init(sf::RenderWindow* window);
	void run(sf::RenderWindow* window);

private:
	std::optional<sf::Sprite> a;
	sf::Texture landTex;
	sf::Texture bgTex;
	std::vector<sf::Sprite> lands;
	int mapWidth = 14;
	int mapHeight = 10;
	float xOffset;
	float yOffset;

	void createFirstRow();
	void createMiddleRows();
	void createLastRow();
	void draw(sf::RenderWindow* window);
};

