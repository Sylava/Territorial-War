#include <SFML/Graphics.hpp>
#include <vector>
#include "InGame.h"
#include "Player.h"
#include "NPC.h"
#include "Warrior.h"
#include "Inputs.h"

InGame::InGame(sf::RenderWindow* inWindow)
{
    window = inWindow;
}

void InGame::run()
{
    Map map(window);
    Player player(window, &map);
    Warrior npc(window, &map);
    Inputs input(window);

    npc.context.map = &map;
    npc.context.player = &player;
    npc.Init();

    sf::Clock clock;
    while (running)
    {
        float dt = clock.restart().asSeconds();
        sf::Vector2f direction = input.manageInputs(player, dt, running);

        player.move(direction * dt, &map);
        player.update(dt);
        npc.update(dt);
        window->clear();
        map.draw();
        player.draw();
        npc.draw();
        window->display();
    }
}