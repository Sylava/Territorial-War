#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "NPC.h"

class CollisionBox
{
public:
    static void HandlePlayerWindowCollision(Player& player, const sf::RenderWindow& window, const sf::Vector2f& oldPos);

    static void HandlePlayerNpcCollision(Player& player, Npc& npc,
        const sf::Vector2f& oldPlayerPos,
        const sf::Vector2f& oldNpcPos);
};


