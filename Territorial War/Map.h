#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
public:
	Map(sf::RenderWindow* inWindow);

	std::vector<sf::Sprite> rocks;
	float top;
	float bottom;
	float left;
	float right;

	void draw();

private:
	sf::RenderWindow* window;
	sf::Texture bgTex;
	sf::Texture rockTex;
	sf::Texture rock2Tex;
	sf::Texture landTex;
	std::vector<sf::Sprite> tiles;
	std::optional<sf::Sprite> background;
	int mapWidth = 22;
	int mapHeight = 14;
	float xOffset;
	float yOffset;

	void createFirstRow();
	void createMiddleRows();
	void createLastRow();
	void createRocksRow();
	void createRock(const sf::Vector2f& position);
};

