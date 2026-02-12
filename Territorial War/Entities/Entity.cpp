#include <iostream>
#include "Entity.h"
#include "../TextureManager.h"

Entity::Entity(sf::RenderWindow* inWindow, int inHp)
{
	hpMax = inHp;
	hp = inHp;
	window = inWindow;
	buildHpBar();
}

void Entity::buildHpBar()
{
	sf::IntRect rect({ 49, 22 }, { 14, 18 });
	startBar.emplace(*TextureManager::loadTexture("assets/hpBar.png"), rect);
	rect = sf::IntRect({ 128, 22 }, { 64, 18 });
	for (int i = 2; i < hpMax; ++i)
	{
		sf::Sprite sprite(*TextureManager::loadTexture("assets/hpBar.png"), rect);
		sprite.setScale({ 0.25f, 1.f });
		middleBar.push_back(sprite);
	}
	rect = sf::IntRect({ 256, 22 }, { 14, 18 });
	endBar.emplace(*TextureManager::loadTexture("assets/hpBar.png"), rect);

	rect = sf::IntRect({ 0, 30 }, { 8, 3 });
	firstHp.emplace(*TextureManager::loadTexture("assets/hpBarFill.png"), rect);
	lastHp.emplace(*TextureManager::loadTexture("assets/hpBarFill.png"), rect);
	rect = sf::IntRect({ 0, 30 }, { 16, 3 });
	for (int i = 0; i < hpMax - 2; ++i)
	{
		sf::Sprite sprite(*TextureManager::loadTexture("assets/hpBarFill.png"), rect);
		hpFill.push_back(sprite);
	}
}

sf::Sprite* Entity::attackAnimation(const float dt)
{
	sf::IntRect rect;
	attackAnimTime -= dt;
	if (attackAnimTime <= 0.f)
	{
		attackAnimTime = 0.08f;
		attackIndex++;
	}
	if (attackIndex > attackMaxIndex)
		rect = sf::IntRect({ (attackMaxIndex * 192) + 192, 0 }, { 192, 192 });
	else
		rect = sf::IntRect({ (attackIndex * 192), 0 }, { 192, 192 });

	spriteAttack->setTextureRect(rect);
	if (attackIndex > attackMaxIndex)
	{
		isAttacking = false;
		attackIndex = 0;
	}
	return &*spriteAttack;
}

sf::Sprite* Entity::runAnimation(const float dt)
{
	runAnimTime -= dt;
	if (runAnimTime <= 0.f)
	{
		runAnimTime = 0.08f;
		if (!runReverse)
		{
			runIndex++;
			if (runIndex > runMaxIndex)
			{
				runIndex = runMaxIndex - 1;
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
	sf::IntRect rect({ runIndex * 192, 0 }, { 192, 192 });
	spriteRun->setTextureRect(rect);
	return &*spriteRun;
}

sf::Sprite* Entity::idleAnimation(const float dt)
{
	idleAnimTime -= dt;
	if (idleAnimTime <= 0.f)
	{
		idleAnimTime = 0.08f;
		if (!idleReverse)
		{
			idleIndex++;
			if (idleIndex > idleMaxIndex)
			{
				idleIndex = idleMaxIndex - 1;
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
	sf::IntRect rect({ idleIndex * 192, 0 }, { 192, 192 });
	spriteIdle->setTextureRect(rect);
	return &*spriteIdle;
}

void Entity::update(const float dt)
{
	invunerability += dt;
	if (isAttacking)
		currentSprite = attackAnimation(dt);
	else if (isMoving)
		currentSprite = runAnimation(dt);
	else
		currentSprite = idleAnimation(dt);
	sf::FloatRect bounds = currentSprite->getLocalBounds();
	currentSprite->setOrigin({ bounds.size.x / 2.f,bounds.size.y / 2.f });
	currentSprite->setScale({ animMirror ? 1.f : -1.f, 1.f });
	currentSprite->setPosition(position);
	updateHpBar();
}

void Entity::updateHpBar()
{
	float xOffset = hpMax * 6;
	startBar->setPosition({ xOffset + position.x - 14 - ((hpMax - 2) * 16), position.y - 70 });
	if (hpMax > 2)
	{
		for (int i = 0; i < hpMax - 2; ++i)
		{
			middleBar[i].setPosition({ xOffset + position.x - 16 * (hpMax - i - 2), position.y - 70 });
		}
	}
	endBar->setPosition({ xOffset + position.x, position.y - 70 });
	firstHp->setPosition({ xOffset + position.x - 6 - ((hpMax - 2) * 16), position.y - 62 });
	if (hpMax > 2)
	{
		for (int i = 0; i < hpMax - 2; ++i)
		{
			hpFill[i].setPosition({ xOffset + position.x - 16 * (hpMax - i - 2), position.y - 62 });
		}
	}
	lastHp->setPosition({ xOffset + position.x, position.y - 62 });
}

void Entity::draw()
{
	window->draw(*currentSprite);
	window->draw(*startBar);
	for (auto sprite : middleBar)
	{
		window->draw(sprite);
	}
	window->draw(*endBar);
	if (hp >= 1)
		window->draw(*firstHp);
	int hpToDraw = 2;
	for (auto sprite : hpFill)
	{
		if (hpToDraw <= hp)
		{
			window->draw(sprite);
			hpToDraw++;
		}
		else
		{
			break;
		}
	}
	if (hp == hpMax)
		window->draw(*lastHp);
}