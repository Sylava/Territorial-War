#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "Map.h"


class InGame
{
public:
	InGame(sf::RenderWindow* inWindow);
	void run();

private:
	sf::RenderWindow* window;
	bool running = true;
};

