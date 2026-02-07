#include "ChaseState.h"
#include "NPC.h"
#include <random>

void ChaseState::Enter(NpcContext& _context)
{
    std::cout << "Enter Chase State" << std::endl;
    _context.npc->isMoving = true;
}

void ChaseState::Execute(NpcContext& _context, float dt)
{

}

void ChaseState::Exit(NpcContext& _context)
{

}