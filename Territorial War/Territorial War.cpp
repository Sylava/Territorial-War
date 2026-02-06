//#include <SFML/Graphics.hpp>
//#include "Player.h"
//
//#include "NPC.h"
//#include "Entity.h"
//#include <vector>
//#include "ColisionBox.h"
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML works!");
//   
//
//    Player player; 
//    Npc npc;
//
//    npc.Init();
//
//    sf::Clock clock;
//
  /*  while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }*/
//        float dt = clock.restart().asSeconds();
//        sf::Vector2f oldPlayerPos = player.getPosition();
//        sf::Vector2f oldNpcPos = npc.getPosition();
//
//        npc.update(dt);
//
//        player.update(dt);
//        // Collision
//        CollisionBox::HandlePlayerWindowCollision(player, window, oldPlayerPos);
//        CollisionBox::HandlePlayerNpcCollision(player, npc, oldPlayerPos, oldNpcPos);
//        window.clear(); 
//        player.draw(window);
//        npc.draw(window);
//        window.display();
//    }
//}
//


#include <SFML/Graphics.hpp>
#include "Npc.h"
#include "Player.h"
#include "Obstacle.h"
#include "CollisionObstacle.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "IA + Obstacles");

    Player player;
    player.setPosition({ 400.f, 300.f });

    Npc npc1;
    npc1.setPosition({ 100.f, 100.f });
    npc1.Init(&player);

    Npc npc2;
    npc2.setPosition({ 700.f, 500.f });
    npc2.Init(&player);

    Obstacle obs1;
    Obstacle obs2;
    Obstacle obs3;

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();

        // Update
        player.update(dt);
        npc1.update(dt);
        npc2.update(dt);

        // Collisions Player ↔ Obstacles
        resolveCollision(player, obs1);
        resolveCollision(player, obs2);
        resolveCollision(player, obs3);

        // Collisions NPC ↔ Obstacles
        resolveCollision(npc1, obs1);
        resolveCollision(npc1, obs2);
        resolveCollision(npc1, obs3);

        resolveCollision(npc2, obs1);
        resolveCollision(npc2, obs2);
        resolveCollision(npc2, obs3);

        // (optionnel) collision joueur ↔ NPC
        if (rectIntersects(player.getShape().getGlobalBounds(),
            npc1.getShape().getGlobalBounds()))
            npc1.getShape().setFillColor(sf::Color::Magenta);
        else
            npc1.getShape().setFillColor(sf::Color::Red);

        if (rectIntersects(player.getShape().getGlobalBounds(),
            npc2.getShape().getGlobalBounds()))
            npc2.getShape().setFillColor(sf::Color::Magenta);
        else
            npc2.getShape().setFillColor(sf::Color::Red);

        window.clear();
        window.draw(player.getShape());
        window.draw(npc1.getShape());
        window.draw(npc2.getShape());
        window.draw(obs1.getShape());
        window.draw(obs2.getShape());
        window.draw(obs3.getShape());
        window.display();
    }

    return 0;
}
