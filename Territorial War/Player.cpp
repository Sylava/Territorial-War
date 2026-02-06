#include "Player.h"
#include <iostream>

Player::Player(sf::RenderWindow* inWindow)
{
	window = inWindow;
	if (!idleTex.loadFromFile("assets/Warrior_Idle.png"))
		std::cout << "texture non chargee" << std::endl;
	if (!runTex.loadFromFile("assets/Warrior_Run.png"))
		std::cout << "texture non chargee" << std::endl;
	position.x = 50.f;
	position.y = 50.f;
}

void Player::update(float dt)
{
	sf::IntRect rect;
	if (isMoving && !wasMoving)
	{
		runIndex = 0;
		animTime = 0.1f;
	}
	else if (wasMoving && !isMoving)
	{
		idleIndex = 0;
		animTime = 0.1f;
	}

	animTime -= dt;
	if (isMoving)
	{
		if (animTime <= 0.f)
		{
			animTime = 0.1f;
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
			animTime = 0.1f;
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
		rect = sf::IntRect({ 62 + (idleIndex * 191), 48 }, { 88, 88 });
		playerSprite.emplace(idleTex);
	}
	playerSprite->setTextureRect(rect);
	playerSprite->setPosition(position);
}

void Player::move(const sf::Vector2f& offset)
{
	position += offset;
}

void Player::draw()
{
	window->draw(*playerSprite);
}