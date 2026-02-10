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
	if (!attackTex.loadFromFile("assets/Warrior_Attack1.png"))
		std::cout << "texture non chargee" << std::endl;
	hitbox.size = { 40.f, 76.f };
	position.x = map->left + hitbox.size.x;
	position.y = map->top + hitbox.size.y / 2;
	hitbox.position = { position.x - 20.f, position.y - 38.f };
	attackArea.setRadius(45);
	attackArea.setOrigin({ attackArea.getRadius(), attackArea.getRadius() });
	attackArea.setFillColor(sf::Color::Transparent);
	attackArea.setOutlineColor(sf::Color::Red);
	attackArea.setOutlineThickness(3);
	attackArea.setPosition({position.x + 25, position.y});
}

void Player::update(const float dt)
{
	invunerability += dt;
	if (isAttacking)
		attackAnimation(dt);
	else if (isMoving)
		runAnimation(dt);
	else
		idleAnimation(dt);
	sf::FloatRect bounds = playerSprite->getLocalBounds();
	playerSprite->setOrigin({ bounds.size.x / 2.f,bounds.size.y / 2.f });
	if (!animMirror)
		playerSprite->setScale({ -1.f, 1.f });
	playerSprite->setPosition(position);
}

void Player::attackAnimation(const float dt)
{
	sf::IntRect rect;
	attackAnimTime -= dt;
	if (attackAnimTime <= 0.f)
	{
		attackAnimTime = 0.08f;
		attackIndex ++;
	}
	if(attackIndex > 3)
		rect = sf::IntRect({ (3 * 192) + 192, 0 }, { 192, 192 });
	else
		rect = sf::IntRect({ (attackIndex * 192), 0 }, { 192, 192 });

	playerSprite.emplace(attackTex);
	playerSprite->setTextureRect(rect);
	if (attackIndex > 3)
	{
		isAttacking = false;
		attackIndex = 0;
	}
}

void Player::runAnimation(const float dt)
{
	runAnimTime -= dt;
	if (runAnimTime <= 0.f)
	{
		runAnimTime = 0.08f;
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
	sf::IntRect rect({runIndex * 192, 0 }, { 192, 192 });
	playerSprite.emplace(runTex);
	playerSprite->setTextureRect(rect);
}

void Player::idleAnimation(const float dt)
{
	idleAnimTime -= dt;
	if (idleAnimTime <= 0.f)
	{
		idleAnimTime = 0.08f;
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
	sf::IntRect rect({idleIndex * 192, 0 }, { 192, 192 });
	playerSprite.emplace(idleTex);
	playerSprite->setTextureRect(rect);
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

void Player::draw()
{
	window->draw(*playerSprite);
}