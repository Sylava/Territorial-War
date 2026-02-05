#pragma once
#include <SFML/Graphics.hpp>


class InGame
{
public:
	void init();
	void run(sf::RenderWindow* window);

private:
	sf::Texture background;

};

