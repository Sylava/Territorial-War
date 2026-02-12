#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "InGame.h"
#include "../Entities/Warrior.h"
#include "../Entities/Healer.h"

InGame::InGame(sf::RenderWindow* inWindow) : window(inWindow), input(Inputs(window))
{
    map = new Map(window);
    player = new Player(window, map);

   
    if (!font.openFromFile("assets/arial.ttf"))
        std::cout << "police non chargee: assets/arial.ttf" << std::endl;
    else
    {
       
        scoreText.emplace(font, "", 24);
        scoreText->setFillColor(sf::Color::White);
    }

   
    WaveInfini();
}

void InGame::run()
{
    sf::Clock clock;
    while (running)
    {
        float dt = clock.restart().asSeconds();
        
        sf::Vector2f direction = input.manageInputs(player, running, score, waveNumber);
        player->move(direction * dt, map);
        player->update(dt);
        npcsUpdate(dt);
        checkHits(player);
        draw();
        checkEndGame();

       
        if (npcs.empty() && running && player->hp > 0)
        {
           
            score += waveNumber * waveBonusMultiplier;
            std::cout << "Vague " << waveNumber << " terminee. Bonus: " << (waveNumber * waveBonusMultiplier) << " Score total: " << score << std::endl;

            WaveInfini();
        }
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

void InGame::checkHits(Player* player)
{
    for (auto it = npcs.begin(); it != npcs.end(); )
    {
        if ((*it)->type == Type::Warrior && (*it)->attackIndex > 1 && player->invunerability >= 0.4f && circleIntersectsRect((*it)->attackArea, player->hitbox))
        {
            player->invunerability = 0.f;
           
        }
        if (player->attackIndex > 1 && (*it)->invunerability >= 0.4f && circleIntersectsRect(player->attackArea, (*it)->hitbox))
        {
            (*it)->invunerability = 0.f;
            (*it)->hp--;
            if ((*it)->hp == 1)
                (*it)->runForYourLife = true;
        }
        if ((*it)->hp <= 0)
        {
            
            score += pointsPerNpc;

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

void InGame::npcsDraw()
{
    for (Npc* npc : npcs)
    {
        npc->draw();
    }
}

void InGame::checkEndGame()
{
    if (player->hp <= 0)
        endScreen(false);
  
}

void InGame::endScreen(bool win)
{
    running = false;
    std::string path;
    if (win)
        path = "assets/win.png";
    else
        path = "assets/gameover.png";
    if (!endTex.loadFromFile(path))
        std::cout << "texture non chargee" << std::endl;
    end.emplace(endTex);
    sf::FloatRect bounds = end->getLocalBounds();
    end->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    end->setPosition({ (float)window->getSize().x / 2, ((float)window->getSize().y / 2) - 80 });
    sf::IntRect rect({ 33, 0 }, { 25, 17 });
    if (!homeTex.loadFromFile("assets/ButtonHome.png", false, rect))
        std::cout << "texture non chargee" << std::endl;
    home.emplace(homeTex);
    home->setScale({ 8.f, 7.f });
    bounds = home->getLocalBounds();
    home->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    home->setPosition({ (float)window->getSize().x / 2, ((float)window->getSize().y / 2) + 80 });

  
    if (scoreText)
    {
        scoreText->setString("Score: " + std::to_string(score) + "  Wave: " + std::to_string(waveNumber));
        sf::FloatRect tbc = scoreText->getLocalBounds();
      
        scoreText->setOrigin({ tbc.position.x + tbc.size.x / 2.f, tbc.position.y + tbc.size.y / 2.f });
        scoreText->setPosition({ (float)window->getSize().x / 2.f, 20.f });
    }

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
        if (scoreText)
            window->draw(*scoreText);
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

      
        if (scoreText)
        {
            scoreText->setString("Score: " + std::to_string(score) + "  Wave: " + std::to_string(waveNumber));
            sf::FloatRect tbw = scoreText->getLocalBounds();
           
            scoreText->setOrigin({ tbw.position.x + tbw.size.x / 2.f, tbw.position.y + tbw.size.y / 2.f });
            scoreText->setPosition({ (float)window->getSize().x / 2.f, 20.f });
            window->draw(*scoreText);
        }

        window->display();
    }
}



void InGame::WaveInfini()
{

    waveNumber++;
    if (waveNumber >= waveNumbermax)
        running = false;
    int computed = 2 << (waveNumber - 1);
    if (computed > maxNpcs)
        targetNpcCount = maxNpcs;
    else
        targetNpcCount = computed;

    std::cout << "Lancement vague " << waveNumber << " : " << targetNpcCount << " ennemis" << std::endl;

    for (int i = 0; i < targetNpcCount; ++i)
    {
        int type = rand() % 2;
        if (type == 0)
            npcs.push_back(new Warrior(window, map));
        else
            npcs.push_back(new Healer(window, map));
    }


    npcsInit(map);
}