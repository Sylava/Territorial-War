#include <SFML/Graphics.hpp>
#include <vector>
#include "InGame.h"
#include "LoadFiles.h"
#include "Player.h"
#include "NPC.h"
#include "Entity.h"

void InGame::init(sf::RenderWindow* window)
{
    if(!landTex.loadFromFile("assets/tiles.png"))
        std::cout << "texture non chargee" << std::endl;
    bgTex = LoadFiles::loadTexture("assets/background.png");
    a.emplace(landTex);
    a->setPosition({ 0, 500 });

    xOffset = (window->getSize().x - ((float)mapWidth * 64)) / 2;
    yOffset = (window->getSize().y - ((float)mapHeight * 64)) / 2;

    createFirstRow();
    createMiddleRows();
    createLastRow();
}

void InGame::run(sf::RenderWindow* window)
{

    Player player;
    Npc npc;
    sf::Sprite background(bgTex);
    auto winSize = window->getSize();
    auto texSize = bgTex.getSize();

    background.setScale({ static_cast<float>(winSize.x) / texSize.x, static_cast<float>(winSize.y) / texSize.y });

    npc.Init();

    sf::Clock clock;

    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window->close();
            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = event->getIf<sf::Event::KeyPressed>();
                if (key->code == sf::Keyboard::Key::Escape)
                    window->close();
            }
        }
        float dt = clock.restart().asSeconds();
        sf::Vector2f oldPlayerPos = player.getPosition();
        sf::Vector2f oldSquarePos = npc.getPosition();

        npc.update(dt);
        player.update(dt);

        // Collision
        if (player.getBounds().findIntersection(npc.getBounds()))
        {
            player.setPosition(oldPlayerPos);
            npc.setPosition(oldSquarePos);
        }
        window->clear();
        window->draw(background);
        draw(window);
        player.draw(window);
        npc.draw(window);
        //window->draw(*a);
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
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + 0, yOffset + 0 });
            lands.push_back(sprite);
        }
        else if(i < mapWidth - 1)
        {
            sf::IntRect rect({ 384, 0 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + 64 * (float)i, yOffset + 0 });
            lands.push_back(sprite);
        }
        else
        {
            sf::IntRect rect({ 448, 0 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + ((float)mapWidth - 1.f) * 64, yOffset + 0 });
            lands.push_back(sprite);
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
                sf::Sprite sprite = (LoadFiles::createSprite(rect, landTex));
                sprite.setPosition({ xOffset + 0, yOffset + (float)y * 64 + 64 });
                lands.push_back(sprite);
            }
            else if (x < mapWidth - 1)
            {
                sf::IntRect rect({ 384, 64 }, { 64, 64 });
                sf::Sprite sprite = (LoadFiles::createSprite(rect, landTex));
                sprite.setPosition({ xOffset + 64 * (float)x, yOffset + 64 * ((float)y + 1) });
                lands.push_back(sprite);
            }
            else
            {
                sf::IntRect rect({ 448, 64 }, { 64, 64 });
                sf::Sprite sprite = (LoadFiles::createSprite(rect, landTex));
                sprite.setPosition({ xOffset + ((float)mapWidth - 1.f) * 64, yOffset + 64 * ((float)y + 1) });
                lands.push_back(sprite);
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
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + 0, yOffset + ((float)mapHeight - 1) * 64 });
            lands.push_back(sprite);
        }
        else if (i < mapWidth - 1)
        {
            sf::IntRect rect({ 384, 128 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset+ 64 * (float)i, yOffset + ((float)mapHeight - 1) * 64 });
            lands.push_back(sprite);
        }
        else
        {
            sf::IntRect rect({ 448, 128 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset+((float)mapWidth - 1.f) * 64, yOffset + ((float)mapHeight - 1) * 64 });
            lands.push_back(sprite);
        }
    }
}

void InGame::draw(sf::RenderWindow* window)
{
    for (sf::Sprite sprite : lands)
    {
        window->draw(sprite);
    }
}