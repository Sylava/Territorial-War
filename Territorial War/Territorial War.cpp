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
    //while (window.isOpen())
    //{
    //    while (const std::optional event = window.pollEvent())
    //    {
    //        if (event->is<sf::Event::Closed>())
    //            window.close();
    //    }
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

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "IA complète SFML 3.0");

    Player player;
    player.setPosition({ 400.f, 300.f });

    // --- NPC 1 ---
    Npc npc1;
    npc1.setPosition({ 100.f, 100.f });
    npc1.Init(&player);

    // --- NPC 2 ---
    Npc npc2;
    npc2.setPosition({ 700.f, 500.f });
    npc2.Init(&player);

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

        // Collision simple NPC ↔ Player
        auto checkCollision = [&](Npc& npc) {
            if (player.getShape().getGlobalBounds().findIntersection(
                npc.getShape().getGlobalBounds()))
            {
                npc.getShape().setFillColor(sf::Color::Magenta);
            }
            else npc.getShape().setFillColor(sf::Color::Red);
        };

        checkCollision(npc1);
        checkCollision(npc2);

        // Draw
        window.clear();
        window.draw(player.getShape());
        window.draw(npc1.getShape());
        window.draw(npc2.getShape());
        window.display();
    }

    return 0;
}
