#include <SFML/Graphics.hpp>
#include "Player.h"

#include "NPC.h"
#include "Entity.h"
#include <vector>

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

        player.update(speed);
        ennemies.update(speed);


        sf::Vector2u winSize = window.getSize();
        float winW = static_cast<float>(winSize.x);
        float winH = static_cast<float>(winSize.y);


        auto clampPosToWindow = [&](const sf::FloatRect& bounds, sf::Vector2f pos) -> sf::Vector2f
            {
                float maxX = std::max(0.f, winW - bounds.size.x);
                float maxY = std::max(0.f, winH - bounds.size.y);
                pos.x = std::clamp(pos.x, 0.f, maxX);
                pos.y = std::clamp(pos.y, 0.f, maxY);
                return pos;
            };

        {
            sf::FloatRect pBounds = player.getBounds();
            sf::Vector2f pPos = player.getPosition();
            pPos = clampPosToWindow(pBounds, pPos);
            player.setPosition(pPos);
        }

        player.update(dt);
        // --- Collision avec les bords de la fenêtre ---
        sf::FloatRect playerBounds = player.getBounds();
        sf::Vector2u winSize = window.getSize();

        if (playerBounds.position.x < 0.f ||
            playerBounds.position.y < 0.f ||
            playerBounds.position.x + playerBounds.size.x > static_cast<float>(winSize.x) ||
            playerBounds.position.y + playerBounds.size.y > static_cast<float>(winSize.y))
        {
           
            player.setPosition(oldPlayerPos);
            // On peut aussi recalculer les bounds si besoin
            playerBounds = player.getBounds();
        }
        // Collision
        if (player.getBounds().findIntersection(npc.getBounds()))
        {   
            player.setPosition(oldPlayerPos);
            ennemies.setPosition(oldSquarePos);
        }

        
        window.clear(sf::Color::Black);
        player.draw(window);
        ennemies.draw(window);
        window.display();

    }
}