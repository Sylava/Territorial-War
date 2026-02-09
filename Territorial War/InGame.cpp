#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "InGame.h"
#include "Warrior.h"

InGame::InGame(sf::RenderWindow* inWindow)
{
    window = inWindow;
    map = new Map(window);
    player = new Player(window, map);
    input = Inputs(window);
    for (int i = 0; i < 50; ++i)
    {
        npcs.push_back(new Warrior(window, map));
    }
    npcsInit(map);
}

void InGame::run()
{
    sf::Clock clock;
    while (running)
    {
        float dt = clock.restart().asSeconds();
        sf::Vector2f direction = input.manageInputs(player, dt, running);
        player->move(direction * dt, map);
        player->update(dt);
        npcsUpdate(dt);
        checkHits(player);
        window->clear();
        map->draw();
        player->draw();
        npcsDraw();
        window->display();
    }
}

void InGame::npcsDraw()
{
    for (Npc* npc : npcs)
    {
        npc->draw();
    }
}

void InGame::npcsUpdate(float dt)
{
    for (Npc* npc : npcs)
    {
        npc->update(dt);
    }
}

void InGame::npcsInit(Map* map)
{
    for (Npc* npc : npcs)
    {
        npc->Init(map, player);
    }
}

void InGame::checkHits(Player* player)
{
    for (auto it = npcs.begin(); it != npcs.end(); )
    {
        if ((*it)->attackIndex > 1 && player->invunerability >= 0.5f && circleIntersectsRect((*it)->attackArea, player->hitbox))
        {
            player->invunerability = 0.f;
            player->hp--;
            /*if (player->hp <= 0)
            {
                delete player;
                player = nullptr;
                return;
            }*/
        }
        if (player->attackIndex > 1 && (*it)->invunerability >= 0.5f && circleIntersectsRect(player->attackArea, (*it)->hitbox))
        {
            (*it)->invunerability = 0.f;
            (*it)->hp--;

        }
        if ((*it)->hp <= 0)
        {
            delete* it;
            it = npcs.erase(it);
            break;
        }
        else
        {
            ++it;
        }
    }

}

bool InGame::circleIntersectsRect(const sf::CircleShape& circle, const sf::FloatRect& rect)
{
    sf::Vector2f center = circle.getPosition();
    float radius = circle.getRadius();
    float left = rect.position.x;
    float right = rect.position.x + rect.size.x;
    float top = rect.position.y;
    float bottom = rect.position.y + rect.size.y;
    float closestX = std::clamp(center.x, left, right);
    float closestY = std::clamp(center.y, top, bottom);
    float dx = center.x - closestX;
    float dy = center.y - closestY;

    return (dx * dx + dy * dy) <= (radius * radius);
}