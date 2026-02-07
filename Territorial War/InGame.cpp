#include <SFML/Graphics.hpp>
#include <vector>
#include "InGame.h"
#include "Player.h"
#include "NPC.h"
#include "Warrior.h"

InGame::InGame(sf::RenderWindow* inWindow)
{
    window = inWindow;
    xOffset = (window->getSize().x - ((float)mapWidth * 64)) / 2;
    yOffset = (window->getSize().y - ((float)mapHeight * 64)) / 2;
    if (!mapTex.loadFromFile("assets/tiles.png"))
        std::cout << "texture non chargee" << std::endl;
    if (!bgTex.loadFromFile("assets/background.png"))
        std::cout << "texture non chargee" << std::endl;
    background.emplace(bgTex);
    auto winSize = window->getSize();
    auto texSize = bgTex.getSize();
    background->setScale({ (float)(winSize.x) / texSize.x, (float)(winSize.y) / texSize.y });


    createFirstRow();
    createMiddleRows();
    createLastRow();
}

void InGame::run()
{
    Player player(window);
    Warrior npc(window);
    npc.context.player = &player;
    npc.Init();

    sf::Clock clock;
    while (running)
    {
        float dt = clock.restart().asSeconds();
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
            player.direction = false;
            player.move({ -player.speed * dt, 0.f });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.isMoving = true;
            player.direction = true;
            player.move({ player.speed * dt, 0.f });
        }
        player.update(dt);
        npc.update(dt);
        player.wasMoving = player.isMoving;
        window->clear();
        draw();
        player.draw();
        npc.draw();
        window->display();
    }
}

void InGame::createFirstRow()
{
    for (int i = 0; i < mapWidth; ++i)
    {
        if (i == 0)
        {
            sf::IntRect rect({ 320, 0 }, { 64, 64 });
            sf::Sprite sprite(mapTex, rect);
            sprite.setPosition({ xOffset + 0, yOffset + 0 });
            map.push_back(sprite);
        }
        else if(i < mapWidth - 1)
        {
            sf::IntRect rect({ 384, 0 }, { 64, 64 });
            sf::Sprite sprite(mapTex, rect);
            sprite.setPosition({ xOffset + 64 * (float)i, yOffset + 0 });
            map.push_back(sprite);
        }
        else
        {
            sf::IntRect rect({ 448, 0 }, { 64, 64 });
            sf::Sprite sprite(mapTex, rect);
            sprite.setPosition({ xOffset + ((float)mapWidth - 1.f) * 64, yOffset + 0 });
            map.push_back(sprite);
        }
    }
}

void InGame::createMiddleRows()
{
    for (int y = 0; y < mapHeight - 2; ++y)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            if (x == 0)
            {
                sf::IntRect rect({ 320, 64 }, { 64, 64 });
                sf::Sprite sprite(mapTex, rect);
                sprite.setPosition({ xOffset + 0, yOffset + (float)y * 64 + 64 });
                map.push_back(sprite);
            }
            else if (x < mapWidth - 1)
            {
                sf::IntRect rect({ 384, 64 }, { 64, 64 });
                sf::Sprite sprite(mapTex, rect);
                sprite.setPosition({ xOffset + 64 * (float)x, yOffset + 64 * ((float)y + 1) });
                map.push_back(sprite);
            }
            else
            {
                sf::IntRect rect({ 448, 64 }, { 64, 64 });
                sf::Sprite sprite(mapTex, rect);
                sprite.setPosition({ xOffset + ((float)mapWidth - 1.f) * 64, yOffset + 64 * ((float)y + 1) });
                map.push_back(sprite);
            }
        }
    }
}

void InGame::createLastRow()
{
    for (int i = 0; i < mapWidth; ++i)
    {
        if (i == 0)
        {
            sf::IntRect rect({ 320, 128 }, { 64, 64 });
            sf::Sprite sprite(mapTex, rect);
            sprite.setPosition({ xOffset + 0, yOffset + ((float)mapHeight - 1) * 64 });
            map.push_back(sprite);
        }
        else if (i < mapWidth - 1)
        {
            sf::IntRect rect({ 384, 128 }, { 64, 64 });
            sf::Sprite sprite(mapTex, rect);
            sprite.setPosition({ xOffset+ 64 * (float)i, yOffset + ((float)mapHeight - 1) * 64 });
            map.push_back(sprite);
        }
        else
        {
            sf::IntRect rect({ 448, 128 }, { 64, 64 });
            sf::Sprite sprite(mapTex, rect);
            sprite.setPosition({ xOffset+((float)mapWidth - 1.f) * 64, yOffset + ((float)mapHeight - 1) * 64 });
            map.push_back(sprite);
        }
    }
}

void InGame::draw()
{
    window->draw(*background);
    for (sf::Sprite sprite : map)
    {
        window->draw(sprite);
    }
}