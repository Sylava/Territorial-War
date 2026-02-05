#include "PatrolState.h"
#include "NPC.h"

void PatrolState::Enter(NpcContext _context)
{
    std::cout << "Enter Patrol _State" << std::endl;
}

void PatrolState::Execute(NpcContext _context)
{
    _context.npc->speed = 500.f;
}

void PatrolState::Exit(NpcContext _context)
{
    std::cout << "Exit Patrol _State" << std::endl;
}