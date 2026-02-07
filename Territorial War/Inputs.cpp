#include "Inputs.h"

Inputs::Inputs(sf::RenderWindow* inWindow)
{
    window = inWindow;
}

void Inputs::manageInputs(Player& player, float& dt, bool& running)
{
    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window->close();
        if (event->is<sf::Event::KeyPressed>())
        {
            auto key = event->getIf<sf::Event::KeyPressed>();
            if (key->code == sf::Keyboard::Key::Escape)
                running = false;
        }
    }
    player.isMoving = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    {
        player.isMoving = true;
        player.move({ 0.f, -player.speed * dt });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        player.isMoving = true;
        player.move({ 0.f, player.speed * dt });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    {
        player.isMoving = true;
        player.animMirror = false;
        player.move({ -player.speed * dt, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        player.isMoving = true;
        player.animMirror = true;
        player.move({ player.speed * dt, 0.f });
    }
}