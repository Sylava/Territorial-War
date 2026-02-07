#include <iostream>
#include "Player.h"
#include "Map.h"

Player::Player(sf::RenderWindow* inWindow, const Map* map)
{
	window = inWindow;
	if (!idleTex.loadFromFile("assets/Warrior_Idle.png"))
		std::cout << "texture non chargee" << std::endl;
	if (!runTex.loadFromFile("assets/Warrior_Run.png"))
		std::cout << "texture non chargee" << std::endl;
	hitbox.size = { 40.f, 80.f };
	position.x = map->left + hitbox.size.x;
	position.y = map->top + hitbox.size.y / 2;
	hitbox.position = { position.x - 20.f, position.y - 40.f };
}

void Player::update(const float dt)
{
	sf::IntRect rect;
	if (isMoving && !wasMoving)
	{
		runIndex = 0;
		animTime = 0.08f;
	}
	else if (wasMoving && !isMoving)
	{
		idleIndex = 0;
		animTime = 0.08f;
	}

	animTime -= dt;
	if (isMoving)
	{
		if (animTime <= 0.f)
		{
			animTime = 0.08f;
			if (!runReverse)
			{
				runIndex++;
				if (runIndex > 5)
				{
					runIndex = 4;
					runReverse = true;
				}
			}
			else
			{
				runIndex--;
				if (runIndex < 0)
				{
					runIndex = 1;
					runReverse = false;
				}
			}
		}
	}
	else
	{
		if (animTime <= 0.f)
		{
			animTime = 0.08f;
			if (!idleReverse)
			{
				idleIndex++;
				if (idleIndex > 7)
				{
					idleIndex = 6;
					idleReverse = true;
				}
			}
			else
			{
				idleIndex--;
				if (idleIndex < 0)
				{
					idleIndex = 1;
					idleReverse = false;
				}
			}
		}
	}
	if (isMoving)
	{
		rect = sf::IntRect({ 62 + (runIndex * 189), 46 }, { 92, 90 });
		playerSprite.emplace(runTex);
	}
	else
	{
		rect = sf::IntRect({ 62 + (idleIndex * 190), 47 }, { 92, 90 });
		playerSprite.emplace(idleTex);
	}
	playerSprite->setTextureRect(rect);
	sf::FloatRect bounds = playerSprite->getLocalBounds();
	playerSprite->setOrigin({ bounds.size.x / 2.f,bounds.size.y / 2.f });
	if (!animMirror)
		playerSprite->setScale({ -1.f, 1.f });
	playerSprite->setPosition(position);
	wasMoving = isMoving;
}

void Player::move(const sf::Vector2f& move, const Map* map)
{
	sf::Vector2f oldPosition = position;
	sf::FloatRect oldHitbox = hitbox;

	position.x += move.x * speed;
	hitbox.position.x += move.x * speed;
	if (hitbox.position.x > map->left && hitbox.position.x < map->right)
	{
		for (const sf::Sprite& rock : map->rocks)
		{
			if (hitbox.findIntersection(rock.getGlobalBounds()))
			{
				position.x = oldPosition.x;
				hitbox.position.x = oldHitbox.position.x;
				break;
			}
		}
	}
	else
	{
		position.x = oldPosition.x;
		hitbox.position.x = oldHitbox.position.x;
	}

	position.y += move.y * speed;
	hitbox.position.y += move.y * speed;
	if (hitbox.position.y > map->top && hitbox.position.y < map->bottom)
	{
		for (const sf::Sprite& rock : map->rocks)
		{
			if (hitbox.findIntersection(rock.getGlobalBounds()))
			{
				position.y = oldPosition.y;
				hitbox.position.y = oldHitbox.position.y;
				break;
			}
		}
	}
	else
	{
		position.y = oldPosition.y;
		hitbox.position.y = oldHitbox.position.y;
	}
}

void Player::draw()
{
	window->draw(*playerSprite);
}