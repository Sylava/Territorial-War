#include <SFML/Graphics.hpp>
#include <vector>
#include "InGame.h"
#include "LoadFiles.h"
#include "Player.h"
#include "NPC.h"
#include "Entity.h"

void InGame::init()
{
	background = LoadFiles::loadTexture("tiles.png");

}

void InGame::run(sf::RenderWindow* window)
{
    Player player;
    Npc npc;

    npc.Init();

    sf::Clock clock;

    while (window->isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = event->getIf<sf::Event::KeyPressed>();
                if (key->code == sf::Keyboard::Key::Escape)
                    window.close();
            }
        }
        float dt = clock.restart().asSeconds();
        sf::Vector2f oldPlayerPos = player.getPosition();
        sf::Vector2f oldSquarePos = npc.getPosition();

        npc.update(dt);
        player.update(dt);

        // Collision
        if (player.getBounds().findIntersection(npc.getBounds()))
        {
            player.setPosition(oldPlayerPos);
            npc.setPosition(oldSquarePos);
        }
        window.clear();
        player.draw(window);
        npc.draw(window);
        window.display();
    }
}