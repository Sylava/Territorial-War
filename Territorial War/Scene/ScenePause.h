#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "SceneMenu.h"

class ScenePause
{
public:
	
	ScenePause(sf::RenderWindow* inWindow, int score = 0, int wave = 0);
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


	sf::Font font;
	std::optional<sf::Text> scoreText;

	void draw();
};