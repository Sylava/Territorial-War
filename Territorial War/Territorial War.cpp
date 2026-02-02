#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Ennemies.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML works!");
    sf::CircleShape shape(100.f);
   
    Player player; 
    Ennemies ennemies;
    float speed = 0.1f;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        sf::Vector2f oldPlayerPos = player.getPosition();
        sf::Vector2f oldSquarePos = ennemies.getPosition();


    

        player.update(speed); ennemies.update(speed); // Collision
        if (player.getBounds().findIntersection(ennemies.getBounds()))
        {   player.setPosition(oldPlayerPos); 
        ennemies.setPosition(oldSquarePos);
        }
        window.clear(sf::Color::Black); 
        player.draw(window);
        ennemies.draw(window);
        window.display();
    }
}



  

     
     
