#include "Warrior.h"
#include "../FSM/Conditions.h"

Warrior::Warrior(sf::RenderWindow* inWindow, const Map* map)
{
	window = inWindow;
	type = Type::Warrior;
	if (!idleTex.loadFromFile("assets/RedWarrior_Idle.png"))
		std::cout << "texture non chargee" << std::endl;
	if (!runTex.loadFromFile("assets/RedWarrior_Run.png"))
		std::cout << "texture non chargee" << std::endl;
	if (!attackTex.loadFromFile("assets/RedWarrior_Attack1.png"))
		std::cout << "texture non chargee" << std::endl;
	hitbox.size = { 40.f, 76.f };
	position.x = map->right;
	position.y = map->bottom + hitbox.size.y / 2;
	hitbox.position = { position.x - 20.f, position.y - 38.f };
	range = 90.f;
	detectionRadius = 300.f;
	attackArea.setRadius(45);
	attackArea.setOrigin({ attackArea.getRadius(), attackArea.getRadius() });
	attackArea.setPosition({ position.x - 25, position.y });
}

void Warrior::update(const float dt)
{
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

void Warrior::attackAnimation(const float dt)
{
	sf::IntRect rect;
	attackAnimTime -= dt;
	if (attackAnimTime <= 0.f)
	{
		attackAnimTime = 0.08f;
		attackIndex++;
	}
	if (attackIndex > 3)
		rect = sf::IntRect({ (3 * 192) + 192, 0 }, { 192, 192 });
	else
		rect = sf::IntRect({ (attackIndex * 192), 0 }, { 192, 192 });

	npcSprite.emplace(attackTex);
	npcSprite->setTextureRect(rect);
	if (attackIndex > 3)
	{
		attackIndex = 0;
		isAttacking = false;
	}
}

void Warrior::runAnimation(const float dt)
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
	sf::IntRect rect({ runIndex * 192, 0 }, { 192, 192 });
	npcSprite.emplace(runTex);
	npcSprite->setTextureRect(rect);
}

void Warrior::idleAnimation(const float dt)
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
	sf::IntRect rect({ idleIndex * 192, 0 }, { 192, 192 });
	npcSprite.emplace(idleTex);
	npcSprite->setTextureRect(rect);
}

void Warrior::Init(Map* map, Player* player, std::vector<Npc*>* npcs)
{
	context.npc = this;
	context.map = map;
	context.npcs = npcs;
	context.player = player;
	PatrolState* patrolState = fsm.CreateState<PatrolState>();
	ChaseState* chaseState = fsm.CreateState<ChaseState>();
	IdleState* idleState = fsm.CreateState<IdleState>();
	//RunAwayState* idleState = fsm.CreateState<RunAwayState>();

	idleState->AddTransition(Conditions::isSeeingPlayer, chaseState);
	idleState->AddTransition(Conditions::hasWaited, patrolState);
	patrolState->AddTransition(Conditions::isSeeingPlayer, chaseState);
	patrolState->AddTransition(Conditions::hasReachedPoint, idleState);
	chaseState->AddTransition([](NpcContext& _context)
		{
			return !Conditions::isSeeingPlayer(_context);
		}, idleState);

	fsm.Init(patrolState, context);
}

void Warrior::draw()
{
	window->draw(*npcSprite);
}