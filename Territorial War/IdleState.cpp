#include "IdleState.h"
#include "NPC.h"
#include <random>

void IdleState::Enter(NpcContext& context)
{
    std::cout << "Enter Idle State" << std::endl;
    context.npc->isMoving = false;
    context.idleTimer = 0.f;
}

void IdleState::Execute(NpcContext& context, const float dt)
{
    context.idleTimer += dt;
}

void IdleState::Exit(NpcContext& context)
{

}