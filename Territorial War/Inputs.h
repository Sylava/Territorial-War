#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"


class Inputs
{
public:
	Inputs();
	Inputs(sf::RenderWindow* inWindow);

	sf::Vector2f manageInputs(Player* player, const float& dt, bool& running);
private:
	sf::RenderWindow* window;
};

