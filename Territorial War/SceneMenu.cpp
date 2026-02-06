#include "SceneMenu.h"
#include <iostream>
#include "InGame.h"

SceneMenu::SceneMenu(sf::RenderWindow* inWindow)
{
	window = inWindow;
	sf::Vector2u winSize = window->getSize();

	sf::IntRect rect({ 3,79 }, { 69, 29 });
	if(!startTex.loadFromFile("assets/buttons.png", false, rect))
		std::cout << "texture non chargee" << std::endl;
	start.emplace(startTex);
	start->setScale({ 3.f, 3.f });
	sf::FloatRect bounds = start->getLocalBounds();
	start->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	start->setPosition({(float)winSize.x / 2, ((float)winSize.y / 2) - 80});

	rect = sf::IntRect({ 4, 215 }, { 54, 29 });
	if (!exitTex.loadFromFile("assets/buttons.png", false, rect))
		std::cout << "texture non chargee" << std::endl;
	exit.emplace(exitTex);
	exit->setScale({ 3.f, 3.f });
	bounds = exit->getLocalBounds();
	exit->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	exit->setPosition({ ((float)winSize.x / 2), ((float)winSize.y / 2) + 80 });

	if (!bgTex.loadFromFile("assets/menu.jpg"))
		std::cout << "texture background non chargee" << std::endl;
	background.emplace(bgTex);
	sf::Vector2u texSize = bgTex.getSize();
	background->setScale({ (float)(winSize.x) / texSize.x, (float)(winSize.y) / texSize.y });
}

void SceneMenu::run()
{
	while (running)
	{
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window->close();
			if (event->is<sf::Event::KeyPressed>())
			{
				auto key = event->getIf<sf::Event::KeyPressed>();
				if (key->code == sf::Keyboard::Key::Escape)
					window->close();
			}
			else if (event->is<sf::Event::MouseButtonPressed>())
			{
				auto mouse = event->getIf<sf::Event::MouseButtonPressed>();

				if (mouse->button == sf::Mouse::Button::Left)
				{
					sf::Vector2f mousePos = window->mapPixelToCoords(mouse->position);

					if (start->getGlobalBounds().contains(mousePos))
						running = false;
					else if (exit->getGlobalBounds().contains(mousePos))
						window->close();
				}
			}
		}
		window->clear();
		draw();
		window->display();
	}
	InGame game(window);
	game.init();
	game.run();
}

void SceneMenu::draw()
{
	window->draw(*background);
	window->draw(*start);
	window->draw(*exit);
}