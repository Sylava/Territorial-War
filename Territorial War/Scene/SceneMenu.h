#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class SceneMenu
{
public:
	SceneMenu(sf::RenderWindow* inWindow);
	void run();

private:
	sf::RenderWindow* window;
	sf::Texture bgTex;
	sf::Texture startTex;
	sf::Texture exitTex;
	std::optional<sf::Sprite> background;
	std::optional<sf::Sprite> start;
	std::optional<sf::Sprite> exit;
	bool running = true;

	void draw();
};

