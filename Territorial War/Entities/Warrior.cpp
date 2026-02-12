#include "Warrior.h"
#include "../FSM/Conditions.h"
#include "../GameCore/TextureManager.h"

Warrior::Warrior(sf::RenderWindow* inWindow, const Map* map) : Npc(inWindow)
{
	type = Type::Warrior;
	spriteIdle.emplace(*TextureManager::loadTexture("assets/RedWarrior_Idle.png"));
	spriteRun.emplace(*TextureManager::loadTexture("assets/RedWarrior_Run.png"));
	spriteAttack.emplace(*TextureManager::loadTexture("assets/RedWarrior_Attack1.png"));
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

void Warrior::Init(Map* map, Player* player, std::vector<Npc*>* npcs)
{
	context.npc = this;
	context.map = map;
	context.npcs = npcs;
	context.player = player;
	PatrolState* patrolState = fsm.CreateState<PatrolState>();
	ChaseState* chaseState = fsm.CreateState<ChaseState>();
	IdleState* idleState = fsm.CreateState<IdleState>();
	RunAwayState* runAwayState = fsm.CreateState<RunAwayState>();

	idleState->AddTransition(Conditions::isSeeingPlayer, chaseState);
	idleState->AddTransition(Conditions::hasWaited, patrolState);
	patrolState->AddTransition(Conditions::isSeeingPlayer, chaseState);
	patrolState->AddTransition(Conditions::hasReachedPoint, idleState);
	runAwayState->AddTransition(Conditions::hasFlee, patrolState);
	chaseState->AddTransition(Conditions::shouldFlee, runAwayState);
	chaseState->AddTransition([](NpcContext& _context)
		{
			return !Conditions::isSeeingPlayer(_context);
		}, idleState);

	fsm.Init(idleState, context);
}

void Warrior::attack()
{
	if (isAttacking == false)
	{
		isAttacking = true;
	}
}