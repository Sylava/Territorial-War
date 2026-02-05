#include "PatrolState.h"

void PatrolState::Enter(NpcContext _context)
{
    std::cout << "Enter Patrol _State" << std::endl;
}

void PatrolState::Execute(NpcContext _context)
{
	std::cout << "Patrol State update" << std::endl;
}

void PatrolState::Exit(NpcContext _context)
{
    std::cout << "Exit Patrol _State" << std::endl;
}