#include "Map.h"
#include <iostream>

Map::Map(sf::RenderWindow* inWindow)
{
    window = inWindow;
    xOffset = (window->getSize().x - ((float)mapWidth * 64)) / 2;
    yOffset = (window->getSize().y - ((float)mapHeight * 64)) / 2;
    top = yOffset - 30;
    bottom = ((float)mapHeight * 64) + yOffset - 90;
    left = xOffset;
    right = ((float)mapWidth * 64) + xOffset - 40;
    sf::IntRect rect({ 7, 17 }, { 49, 34 });
	if (!bgTex.loadFromFile("assets/background.png"))
		std::cout << "texture non chargee" << std::endl;
	if (!rockTex.loadFromFile("assets/Rock.png", false, rect))
		std::cout << "texture non chargee" << std::endl;
    if (!rock2Tex.loadFromFile("assets/Rock2.png", false, rect))
        std::cout << "texture non chargee" << std::endl;
	if (!landTex.loadFromFile("assets/tiles.png"))
		std::cout << "texture non chargee" << std::endl;

    createFirstRow();
    createMiddleRows();
    createLastRow();
    createRocksRow();
	background.emplace(bgTex);
    auto winSize = window->getSize();
    auto texSize = bgTex.getSize();
    background->setScale({ (float)(winSize.x) / texSize.x, (float)(winSize.y) / texSize.y });
}

void Map::createFirstRow()
{
    for (int i = 0; i < mapWidth; ++i)
    {
        if (i == 0)
        {
            sf::IntRect rect({ 320, 0 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + 0, yOffset + 0 });
            tiles.push_back(sprite);
        }
        else if (i < mapWidth - 1)
        {
            sf::IntRect rect({ 384, 0 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + 64 * (float)i, yOffset + 0 });
            tiles.push_back(sprite);
        }
        else
        {
            sf::IntRect rect({ 448, 0 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + ((float)mapWidth - 1.f) * 64, yOffset + 0 });
            tiles.push_back(sprite);
        }
    }
}

void Map::createMiddleRows()
{
    for (int y = 0; y < mapHeight - 2; ++y)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            sf::IntRect rect;
            sf::Vector2f position;

            if (x == 0)
            {
                rect = sf::IntRect({ 320, 64 }, { 64, 64 });
                position = { xOffset, yOffset + y * 64.f + 64.f };
            }
            else if (x < mapWidth - 1)
            {
                rect = sf::IntRect({ 384, 64 }, { 64, 64 });
                position = { xOffset + 64.f * x, yOffset + 64.f * (y + 1) };
            }
            else
            {
                rect = sf::IntRect({ 448, 64 }, { 64, 64 });
                position = { xOffset + (mapWidth - 1.f) * 64.f, yOffset + 64.f * (y + 1) };
            }

            sf::Sprite tile(landTex, rect);
            tile.setPosition(position);
            tiles.push_back(tile);
            createRock(position);
        }
    }
}

void Map::createLastRow()
{
    for (int i = 0; i < mapWidth; ++i)
    {
        if (i == 0)
        {
            sf::IntRect rect({ 320, 128 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + 0, yOffset + ((float)mapHeight - 1) * 64 });
            tiles.push_back(sprite);
        }
        else if (i < mapWidth - 1)
        {
            sf::IntRect rect({ 384, 128 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + 64 * (float)i, yOffset + ((float)mapHeight - 1) * 64 });
            tiles.push_back(sprite);
        }
        else
        {
            sf::IntRect rect({ 448, 128 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + ((float)mapWidth - 1.f) * 64, yOffset + ((float)mapHeight - 1) * 64 });
            tiles.push_back(sprite);
        }
    }
}

void Map::createRocksRow()
{
    for (int i = 0; i < mapWidth; ++i)
    {
        if (i == 0)
        {
            sf::IntRect rect({ 320, 320 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + 0, yOffset + ((float)mapHeight) * 64 });
            tiles.push_back(sprite);
        }
        else if (i < mapWidth - 1)
        {
            sf::IntRect rect({ 384, 320 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + 64 * (float)i, yOffset + ((float)mapHeight) * 64 });
            tiles.push_back(sprite);
        }
        else
        {
            sf::IntRect rect({ 448, 320 }, { 64, 64 });
            sf::Sprite sprite(landTex, rect);
            sprite.setPosition({ xOffset + ((float)mapWidth - 1.f) * 64, yOffset + ((float)mapHeight) * 64 });
            tiles.push_back(sprite);
        }
    }
}

void Map::createRock(const sf::Vector2f& position)
{
    if ((std::rand() % 9) == 0)
    {
        sf::Sprite rock(rockTex);
        rock.setPosition(position);
        rocks.push_back(rock);
    }
}

void Map::draw()
{
    window->draw(*background);
    for (sf::Sprite sprite : tiles)
    {
        window->draw(sprite);
    }
    for (sf::Sprite sprite : rocks)
    {
        window->draw(sprite);
    }
}