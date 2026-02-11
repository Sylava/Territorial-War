#include <SFML/Graphics.hpp>
#include "Inputs.h"
#include "Scene/ScenePause.h"


Inputs::Inputs(sf::RenderWindow* inWindow)
{
    window = inWindow;
}

sf::Vector2f Inputs::manageInputs(Player* player, bool& running)
{
    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window->close();
        if (event->is<sf::Event::KeyPressed>())
        { 
            auto key = event->getIf<sf::Event::KeyPressed>();
            if (key->code == sf::Keyboard::Key::Escape)
            {
                ScenePause pause(window);
                running = pause.run();
            }
        }
        
    }
    sf::Vector2f direction{ 0.f, 0.f };
    player->isMoving = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    {
        player->isMoving = true;
        direction.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        player->isMoving = true;
        direction.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    {
        player->isMoving = true;
        player->animMirror = false;
        direction.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        player->isMoving = true;
        player->animMirror = true;
        direction.x += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        if (player->isAttacking == false)
        {
            player->isAttacking = true;
            player->attackAnimTime = 0.08f;
        }
    }
    return direction;
}