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
    Player player(window);
    Warrior npc(window);
    Inputs input(window);

    npc.context.player = &player;
    npc.Init();

    sf::Clock clock;
    while (running)
    {
        float dt = clock.restart().asSeconds();
        input.manageInputs(player, dt, running);

        player.update(dt);
        npc.update(dt);
        window->clear();
        map.draw();
        player.draw();
        npc.draw();
        window->display();
    }
}