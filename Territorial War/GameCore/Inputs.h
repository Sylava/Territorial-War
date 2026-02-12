#pragma once
#include <SFML/Graphics.hpp>
#include "../Entities/Player.h"


class Inputs
{
public:
	Inputs(sf::RenderWindow* inWindow);

	sf::Vector2f manageInputs(Player* player, bool& running);
private:
	sf::RenderWindow* window;
};

