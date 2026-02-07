#include "Warrior.h"
#include "Map.h"

Warrior::Warrior(sf::RenderWindow* inWindow, const Map* map)
{
	window = inWindow;
	if (!idleTex.loadFromFile("assets/RedWarrior_Idle.png"))
		std::cout << "texture non chargee" << std::endl;
	if (!runTex.loadFromFile("assets/RedWarrior_Run.png"))
		std::cout << "texture non chargee" << std::endl;
	hitbox.size = { 40.f, 80.f };
	position.x = map->right;
	position.y = map->bottom + hitbox.size.y / 2;
	hitbox.position = { position.x - 20.f, position.y - 40.f };
	range = 80.f;
	detectionRadius = 300.f;
}

void Warrior::update(const float dt)
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
	if (!animMirror)
		npcSprite->setScale({ -1.f, 1.f });
	npcSprite->setPosition(position);
	wasMoving = isMoving;
}

void Warrior::draw()
{
	window->draw(*npcSprite);
}