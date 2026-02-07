#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Inputs
{
public:
	Inputs(sf::RenderWindow* inWindow);

	void manageInputs(Player& player, float& dt, bool& running);
private:
	sf::RenderWindow* window;
};

