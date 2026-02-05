#include <SFML/Graphics.hpp>
#include "Player.h"

#include "NPC.h"
#include "Entity.h"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML works!");
   

    Player player; 
    Npc npc;

    npc.Init();

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
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



  

     
     
