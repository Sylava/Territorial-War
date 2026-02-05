#include <SFML/Graphics.hpp>
#include <vector>
#include "InGame.h"
#include "LoadFiles.h"
#include "Player.h"
#include "NPC.h"
#include "Entity.h"

void InGame::init()
{
    landTex = LoadFiles::loadTexture("assets/tiles.png");
    bgTex = LoadFiles::loadTexture("assets/background.png");
    createFirstRow();
    createMiddleRows();

    /*sf::IntRect rect({ 320, 0 }, { 64, 64 });
    lands.push_back(LoadFiles::createSprite(rect, landTex));
    lands[0].setPosition({ 0, 0 });
    sf::IntRect rect2({ 384, 0 }, { 64, 64 });
    lands.push_back(LoadFiles::createSprite(rect2, landTex));
    lands[1].setPosition({ 64, 0 });
    lands.push_back(LoadFiles::createSprite(rect2, landTex));
    lands[2].setPosition({ 128, 0 });
    sf::IntRect rect3({ 448, 0 }, { 64, 64 });
    lands.push_back(LoadFiles::createSprite(rect3, landTex));
    lands[3].setPosition({ 192, 0 });
    sf::IntRect rect4({ 320, 64 }, { 64, 64 });
    lands.push_back(LoadFiles::createSprite(rect4, landTex));
    lands[4].setPosition({ 0, 64 });
    sf::IntRect rect5({ 384, 64 }, { 64, 64 });
    lands.push_back(LoadFiles::createSprite(rect5, landTex));
    lands[5].setPosition({ 64, 64 });
    lands.push_back(LoadFiles::createSprite(rect5, landTex));
    lands[6].setPosition({ 128, 64 });
    sf::IntRect rect6({ 448, 64 }, { 64, 64 });
    lands.push_back(LoadFiles::createSprite(rect6, landTex));
    lands[7].setPosition({ 192, 64 });*/
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
            sf::Sprite sprite = (LoadFiles::createSprite(rect, landTex));
            sprite.setPosition({ 0, 0 });
            lands.push_back(sprite);
        }
        else if(i < mapWidth - 1)
        {
            sf::IntRect rect({ 384, 0 }, { 64, 64 });
            sf::Sprite sprite = (LoadFiles::createSprite(rect, landTex));
            sprite.setPosition({ 64 * (float)i, 0 });
            lands.push_back(sprite);
        }
        else
        {
            sf::IntRect rect({ 448, 0 }, { 64, 64 });
            sf::Sprite sprite = (LoadFiles::createSprite(rect, landTex));
            sprite.setPosition({ ((float)mapWidth - 1.f) * 64, 0 });
            lands.push_back(sprite);
        }
    }
}

void InGame::createMiddleRows()
{
    for (int y = 0; y < mapHeight - 1; ++y)
    {
        for (int x = 0; x < mapWidth; ++y)
        {
            if (x == 0)
            {
                sf::IntRect rect({ 320, 64 }, { 64, 64 });
                sf::Sprite sprite = (LoadFiles::createSprite(rect, landTex));
                sprite.setPosition({ 0, 64 * (float)y });
                lands.push_back(sprite);
            }
            else if (x < mapWidth - 1)
            {
                sf::IntRect rect({ 384, 64 }, { 64, 64 });
                sf::Sprite sprite = (LoadFiles::createSprite(rect, landTex));
                sprite.setPosition({ 64 * (float)x, 64 * (float)y });
                lands.push_back(sprite);
            }
            else
            {
                sf::IntRect rect({ 448, 64 }, { 64, 64 });
                sf::Sprite sprite = (LoadFiles::createSprite(rect, landTex));
                sprite.setPosition({ ((float)mapWidth - 1.f) * 64, 64 * (float)y });
                lands.push_back(sprite);
            }
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