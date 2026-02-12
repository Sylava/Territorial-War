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
	std::optional<sf::Sprite> background;
	std::optional<sf::Sprite> start;
	std::optional<sf::Sprite> exit;
	bool running = true;

	void draw();
};

