#pragma once
#include <SFML/Graphics.hpp>
#include <optional>


class InGame
{
public:
	InGame(sf::RenderWindow* inWindow);
	void run();

private:
	sf::RenderWindow* window;
	sf::Texture mapTex;
	sf::Texture bgTex;
	std::optional<sf::Sprite> background;
	std::vector<sf::Sprite> map;
	int mapWidth = 22;
	int mapHeight = 15;
	float xOffset;
	float yOffset;
	bool running = true;

	void createFirstRow();
	void createMiddleRows();
	void createLastRow();
	void draw();
};

