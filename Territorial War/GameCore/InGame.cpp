#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "InGame.h"
#include "../Entities/Warrior.h"
#include "../Entities/Healer.h"
#include "TextureManager.h"

InGame::InGame(sf::RenderWindow* inWindow) : window(inWindow), input(Inputs(window))
{
    map = new Map(window);
    player = new Player(window, map);
    // création des npcs
    npcs.push_back(new Warrior(window, map));
    npcs.push_back(new Healer(window, map));
    npcsInit(map);
}

void InGame::run()
{
    sf::Clock clock;
    // boucle de la partie
    while (running)
    {
        float dt = clock.restart().asSeconds();
        checkEndGame();
        sf::Vector2f direction = input.manageInputs(player, running);
        player->move(direction * dt, map);
        player->update(dt);
        npcsUpdate(dt);
        checkHits(player);
        draw();
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
        npc->Init(map, player, &npcs);
    }
}

// vérifie si chaque entité reçoit des dégâts
void InGame::checkHits(Player* player)
{
    for (auto it = npcs.begin(); it != npcs.end(); )
    {
        if ((*it)->type == Type::Warrior && (*it)->attackIndex > 1 && player->invunerability >= 0.4f && circleIntersectsRect((*it)->attackArea, player->hitbox))
        {
            player->invunerability = 0.f;
            player->hp--;
        }
        if (player->attackIndex > 1 && (*it)->invunerability >= 0.4f && circleIntersectsRect(player->attackArea, (*it)->hitbox))
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

// collision entre cercle et rectangle
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

void InGame::npcsDraw()
{
    for (Npc* npc : npcs)
    {
        npc->draw();
    }
}

// vérifie si la partie se termine
void InGame::checkEndGame()
{
    if (player->hp <= 0)
        endScreen(false);
    else if (npcs.empty())
        endScreen(true);
}

// gère l'écran de fin
void InGame::endScreen(bool win)
{
    running = false;
    std::string path;
    if (win)
        path = "assets/win.png";
    else
        path = "assets/gameover.png";
    end.emplace(*TextureManager::loadTexture(path));
    sf::FloatRect bounds = end->getLocalBounds();
    end->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    end->setPosition({ (float)window->getSize().x / 2, ((float)window->getSize().y / 2) - 80 });

    sf::IntRect rect({ 33, 0 }, { 25, 17 });
    home.emplace(*TextureManager::loadTexture("assets/ButtonHome.png"), rect);
    home->setScale({ 8.f, 7.f });
    bounds = home->getLocalBounds();
    home->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    home->setPosition({ (float)window->getSize().x / 2, ((float)window->getSize().y / 2) + 80 });

    bool clickedBtn = false;
    while (!clickedBtn)
    {
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window->close();

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                auto mouse = event->getIf<sf::Event::MouseButtonPressed>();

                if (mouse->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos = window->mapPixelToCoords(mouse->position);

                    if (home->getGlobalBounds().contains(mousePos))
                        clickedBtn = true;
                }
            }
        }
        window->clear();
        window->draw(*end);
        window->draw(*home);
        window->display();
    }
}

void InGame::draw()
{
    if (running)
    {
        window->clear();
        map->draw();
        npcsDraw();
        player->draw();
        window->display();
    }
}