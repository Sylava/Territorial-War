#include <iostream>
#include "Healer.h"
#include "../Map.h"
#include "../FSM/Conditions.h"

Healer::Healer(sf::RenderWindow* inWindow, const Map* map)
{
	window = inWindow;
	type = Type::Healer;
	if (!idleTex.loadFromFile("assets/HealerIdle.png"))
		std::cout << "texture non chargee" << std::endl;
	if (!runTex.loadFromFile("assets/HealerRun.png"))
		std::cout << "texture non chargee" << std::endl;
	if (!attackTex.loadFromFile("assets/HealerHeal.png"))
		std::cout << "texture non chargee" << std::endl;
	if (!effectTex.loadFromFile("assets/Heal_Effect.png"))
		std::cout << "texture non chargee" << std::endl;
	hitbox.size = { 40.f, 76.f };
	position.x = map->right;
	position.y = map->bottom + hitbox.size.y / 2;
	hitbox.position = { position.x - 20.f, position.y - 38.f };
	range = 500.f;
	detectionRadius = 650.f;
	attackArea.setRadius(0);
	attackArea.setOrigin({ attackArea.getRadius(), attackArea.getRadius() });
	attackArea.setFillColor(sf::Color::Transparent);
	attackArea.setOutlineColor(sf::Color::Red);
	attackArea.setOutlineThickness(3);
	attackArea.setPosition({ position.x, position.y });
}

void Healer::update(const float dt)
{
	skillCD += dt;
	invunerability += dt;
	fsm.Update(context, dt);
	if (isAttacking)
		attackAnimation(dt);
	else if (isMoving)
		runAnimation(dt);
	else
		idleAnimation(dt);
	sf::FloatRect bounds = npcSprite->getLocalBounds();
	npcSprite->setOrigin({ bounds.size.x / 2.f,bounds.size.y / 2.f });
	if (!animMirror)
		npcSprite->setScale({ -1.f, 1.f });
	npcSprite->setPosition(position);
}

void Healer::healAnimation(const float dt)
{
	sf::IntRect rect;
	healAnimTime -= dt;
	if (healAnimTime <= 0.f)
	{
		healAnimTime = 0.08f;
		healIndex++;
	}
	if (healIndex > 10)
	{
		rect = sf::IntRect({ (healIndex * 0), 0 }, { 1, 1 });
		healIndex = 0;
	}
	else
		rect = sf::IntRect({ (healIndex * 192), 0 }, { 192, 192 });
	healEffect.emplace(effectTex);
	healEffect->setTextureRect(rect);
	sf::FloatRect bounds = healEffect->getLocalBounds();
	healEffect->setOrigin({ bounds.size.x / 2.f,bounds.size.y / 2.f });
	healEffect->setPosition(target->position);
}

void Healer::attackAnimation(const float dt)
{
	sf::IntRect rect;
	attackAnimTime -= dt;
	healAnimation(dt);
	if (attackAnimTime <= 0.f)
	{
		attackAnimTime = 0.08f;
		attackIndex++;
	}
	if (attackIndex > 10)
		rect = sf::IntRect({ (9 * 192) + 192, 0 }, { 192, 192 });
	else
		rect = sf::IntRect({ (attackIndex * 192), 0 }, { 192, 192 });

	npcSprite.emplace(attackTex);
	npcSprite->setTextureRect(rect);
	if (attackIndex > 10)
	{
		isAttacking = false;
		skillCD = 0.f;
	}
}

void Healer::runAnimation(const float dt)
{
	runAnimTime -= dt;
	if (runAnimTime <= 0.f)
	{
		runAnimTime = 0.08f;
		if (!runReverse)
		{
			runIndex++;
			if (runIndex > 3)
			{
				runIndex = 2;
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
	npcSprite.emplace(runTex);
	npcSprite->setTextureRect(rect);
}

void Healer::idleAnimation(const float dt)
{
	idleAnimTime -= dt;
	if (idleAnimTime <= 0.f)
	{
		idleAnimTime = 0.08f;
		if (!idleReverse)
		{
			idleIndex++;
			if (idleIndex > 5)
			{
				idleIndex = 4;
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
	npcSprite.emplace(idleTex);
	npcSprite->setTextureRect(rect);
}

void Healer::Init(Map* map, Player* player, std::vector<Npc*>* npcs)
{
	context.npc = this;
	context.npcs = npcs;
	context.map = map;
	context.player = player;
	PatrolState* patrolState = fsm.CreateState<PatrolState>();
	IdleState* idleState = fsm.CreateState<IdleState>();
	HealState* healstate = fsm.CreateState<HealState>();

	idleState->AddTransition(Conditions::hasWaited, patrolState);
	idleState->AddTransition(Conditions::needHealing, healstate);
	patrolState->AddTransition(Conditions::hasReachedPoint, idleState);
	patrolState->AddTransition(Conditions::needHealing, healstate);
	healstate->AddTransition(Conditions::onCooldown, patrolState);

	fsm.Init(patrolState, context);
}

void Healer::draw()
{
	window->draw(*npcSprite);
	if(isAttacking)
		window->draw(*healEffect);
}
