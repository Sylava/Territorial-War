#include <iostream>
#include "Player.h"
#include "../TextureManager.h"

Player::Player(sf::RenderWindow* inWindow, const Map* map) : Entity(inWindow)
{
	spriteIdle.emplace(*TextureManager::loadTexture("assets/Warrior_Idle.png"));
	spriteRun.emplace(*TextureManager::loadTexture("assets/Warrior_Run.png"));
	spriteAttack.emplace(*TextureManager::loadTexture("assets/Warrior_Attack1.png"));
	hitbox.size = { 40.f, 76.f };
	position.x = map->left + hitbox.size.x;
	position.y = map->top + hitbox.size.y / 2;
	hitbox.position = { position.x - 20.f, position.y - 38.f };
	attackArea.setRadius(45);
	attackArea.setOrigin({ attackArea.getRadius(), attackArea.getRadius() });
	attackArea.setFillColor(sf::Color::Transparent);
	attackArea.setPosition({position.x + 25, position.y});
}

void Player::moveOnAxis(float& pos, float& hitboxPos, float delta, float min, float max, const Map* map)
{
	float oldPosition = pos;
	float oldHitbox = hitboxPos;

	pos += delta * speed;
	hitboxPos += delta * speed;

	if (hitboxPos > min && hitboxPos < max)
	{
		for (const sf::Sprite& rock : map->rocks)
		{
			if (hitbox.findIntersection(rock.getGlobalBounds()))
			{
				pos = oldPosition;
				hitboxPos = oldHitbox;
				break;
			}
		}
	}
	else
	{
		pos = oldPosition;
		hitboxPos = oldHitbox;
	}
}


void Player::move(const sf::Vector2f& move, const Map* map)
{
	moveOnAxis(position.x, hitbox.position.x, move.x, map->left, map->right, map);
	moveOnAxis(position.y, hitbox.position.y, move.y, map->top, map->bottom, map);
	if(animMirror)
		attackArea.setPosition({ position.x + 25, position.y });
	else
		attackArea.setPosition({ position.x - 25, position.y });
}