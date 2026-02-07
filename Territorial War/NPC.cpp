#include "NPC.h"
#include "Conditions.h"

void Npc::Init()
{
    context.npc = this;
    PatrolState* patrolState = fsm.CreateState<PatrolState>();
    ChaseState* chaseState = fsm.CreateState<ChaseState>();
    IdleState* idleState = fsm.CreateState<IdleState>();

    idleState->AddTransition(Conditions::IsSeeingPlayer, chaseState);
    idleState->AddTransition(Conditions::HasWaited, patrolState);
    patrolState->AddTransition(Conditions::IsSeeingPlayer, chaseState);
    patrolState->AddTransition(Conditions::HasReachedPoint, idleState);

    chaseState->AddTransition([](NpcContext& _context)
        {
            return !Conditions::IsSeeingPlayer(_context);
        }, patrolState);

    fsm.Init(patrolState, context);
}

void Npc::updateFsm(float dt)
{
    fsm.Update(context, dt);
}

void Npc::move(const sf::Vector2f& movement)
{
    if (movement.x > 0.f)
        animMirror = true;
    else if (movement.x < 0.f)
        animMirror = false;
    position += movement;
}