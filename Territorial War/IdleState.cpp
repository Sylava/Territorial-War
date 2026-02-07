#include "IdleState.h"
#include "NPC.h"
#include <random>

void IdleState::Enter(NpcContext& _context)
{
    std::cout << "Enter Idle State" << std::endl;
    _context.npc->isMoving = false;
    _context.idleTimer = 0.f;
}

void IdleState::Execute(NpcContext& _context, float dt)
{
    _context.idleTimer += dt;
}

void IdleState::Exit(NpcContext& _context)
{

}