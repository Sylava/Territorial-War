#include "ScenePause.h"

#include <iostream>
#include "InGame.h"

ScenePause::ScenePause(sf::RenderWindow* inWindow)
{
	window = inWindow;
	sf::Vector2u winSize = window->getSize();

	sf::IntRect rect({ 3,71 }, { 68, 211 - 71 });
	if (!ContinuesTex.loadFromFile("assets/buttons.png", false, rect))
		std::cout << "texture non chargee" << std::endl;
	Continues.emplace(ContinuesTex);
	Continues->setScale({ 3.f, 3.f });
	sf::FloatRect bounds = Continues->getLocalBounds();
	Continues->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	Continues->setPosition({ (float)winSize.x / 2, ((float)winSize.y / 2) - 80 });

	rect = sf::IntRect({ 4, 215 }, { 54, 29 });
	if (!MenuTex.loadFromFile("assets/buttons.png", false, rect))
		std::cout << "texture non chargee" << std::endl;
	Menu.emplace(MenuTex);
	Menu->setScale({ 3.f, 3.f });
	bounds = Menu->getLocalBounds();
	Menu->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	Menu->setPosition({ ((float)winSize.x / 2), ((float)winSize.y / 2) + 80 });

	if (!bgTex.loadFromFile("assets/menu.jpg"))
		std::cout << "texture background non chargee" << std::endl;
	background.emplace(bgTex);
	sf::Vector2u texSize = bgTex.getSize();
	background->setScale({ (float)(winSize.x) / texSize.x, (float)(winSize.y) / texSize.y });
}

void ScenePause::run()
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

					if (Continues->getGlobalBounds().contains(mousePos))
						running = false;
					else if (Menu->getGlobalBounds().contains(mousePos))
						window->close();
				}
			}
		}
		window->clear();
		draw();
		window->display();
	}
	InGame game(window);
	game.run();
}

void ScenePause::draw()
{
	window->draw(*background);
	window->draw(*Continues);
	window->draw(*Menu);
}