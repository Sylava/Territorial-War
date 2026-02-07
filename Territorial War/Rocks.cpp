#include "Rocks.h"
#include <iostream>

Rocks::Rocks()
{
	if (!rockTex.loadFromFile("assets/Warrior_Idle.png"))
		std::cout << "texture non chargee" << std::endl;
}