#include "ScenePause.h"
#include <iostream>
#include "InGame.h"

ScenePause::ScenePause(sf::RenderWindow* inWindow)
{
	window = inWindow;
	sf::Vector2u winSize = window->getSize();

	sf::IntRect rect({ 0,0 }, { 26, 16 });
	if (!ContinuesTex.loadFromFile("assets/ButtonAgain.png", false, rect))
		std::cout << "texture non chargee" << std::endl;
	Continues.emplace(ContinuesTex);
	Continues->setScale({ 8.f, 7.f });
	sf::FloatRect bounds = Continues->getLocalBounds();
	Continues->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	Continues->setPosition({ (float)winSize.x / 2, ((float)winSize.y / 2) - 90 });

	rect = sf::IntRect({ 33, 0 }, { 24, 16 });
	if (!MenuTex.loadFromFile("assets/ButtonHome.png", false, rect))
		std::cout << "texture non chargee" << std::endl;
	Menu.emplace(MenuTex);
	Menu->setScale({ 8.f, 7.f });
	bounds = Menu->getLocalBounds();
	Menu->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
	Menu->setPosition({ ((float)winSize.x / 2), ((float)winSize.y / 2) + 90 });

	if (!bgTex.loadFromFile("assets/menu.jpg"))
		std::cout << "texture background non chargee" << std::endl;
	background.emplace(bgTex);
	sf::Vector2u texSize = bgTex.getSize();
	background->setScale({ (float)(winSize.x) / texSize.x, (float)(winSize.y) / texSize.y });
}

bool ScenePause::run()
{
	while (running)
	{
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window->close();

			if (event->is<sf::Event::MouseButtonPressed>())
			{
				auto mouse = event->getIf<sf::Event::MouseButtonPressed>();

				if (mouse->button == sf::Mouse::Button::Left)
				{
					sf::Vector2f mousePos = window->mapPixelToCoords(mouse->position);

					if (Continues->getGlobalBounds().contains(mousePos))
						return true;
					else if (Menu->getGlobalBounds().contains(mousePos))
						return false;
				}
			}
		}
		window->clear();
		draw();
		window->display();
	}
}

void ScenePause::draw()
{
	window->draw(*background);
	window->draw(*Continues);
	window->draw(*Menu);
}