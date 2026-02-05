#include "NPC.h"

Npc::~Npc()
{

}

void Npc::Init()
{
    context.npc = this;
    PatrolState* patrolState = fsm.CreateState<PatrolState>();
    ChaseState* chaseState = fsm.CreateState<ChaseState>();

    patrolState->AddTransition(Conditions::IsSeeingPlayer, chaseState);

    chaseState->AddTransition([](const NpcContext _context)
        {
            return !Conditions::IsSeeingPlayer(_context);
        }, patrolState);

    fsm.Init(patrolState, context);
}

void Npc::update(float dt)
{
    fsm.Update(context);
    // calcul de la direction
    if (PointToGo)
    {
        direction = (PointA - getPosition()).normalized();
    }
    else
    {
        direction = (PointB - getPosition()).normalized();
    }
    move(direction * speed * dt);
    if (getPosition().x >= PointA.x)
        PointToGo = false;
    if (getPosition().y >= PointB.y)
        PointToGo = true;
}