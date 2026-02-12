#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "SceneMenu.h"
class ScenePause 
{
public:
	
	ScenePause(sf::RenderWindow* inWindow);
	bool run();

private:
	
	sf::RenderWindow* window;
	sf::Texture bgTex;
	sf::Texture ContinuesTex;
	sf::Texture MenuTex;
	std::optional<sf::Sprite> background;
	std::optional<sf::Sprite> Continues;
	std::optional<sf::Sprite> Menu;
	bool running = true;

	void draw();
};



