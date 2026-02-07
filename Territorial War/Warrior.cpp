#include "Warrior.h"

Warrior::Warrior(sf::RenderWindow* inWindow)
{
	window = inWindow;
	if (!idleTex.loadFromFile("assets/RedWarrior_Idle.png"))
		std::cout << "texture non chargee" << std::endl;
	if (!runTex.loadFromFile("assets/RedWarrior_Run.png"))
		std::cout << "texture non chargee" << std::endl;
	position.x = 1200.f;
	position.y = 800.f;
}

void Warrior::update(float dt)
{
	updateFsm(dt);
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
		npcSprite.emplace(runTex);
	}
	else
	{
		rect = sf::IntRect({ 62 + (idleIndex * 190), 47 }, { 92, 90 });
		npcSprite.emplace(idleTex);
	}
	npcSprite->setTextureRect(rect);
	sf::FloatRect bounds = npcSprite->getLocalBounds();
	npcSprite->setOrigin({ bounds.size.x / 2.f,bounds.size.y / 2.f });
	if (!direction)
		npcSprite->setScale({ -1.f, 1.f });
	npcSprite->setPosition(position);
	wasMoving = isMoving;
}

void Warrior::draw()
{
	window->draw(*npcSprite);
}