#include "PatrolState.h"
#include "NPC.h"
#include <random>

void PatrolState::Enter(NpcContext& _context)
{
    std::cout << "Enter Patrol State" << std::endl;
    _context.reachedPoint = false;
    _context.npc->isMoving = true;
    _context.reachedPoint = false;
    setPatrolPoints();
}

void PatrolState::Execute(NpcContext& _context, float dt)
{
    sf::Vector2f pos = _context.npc->position;
    sf::Vector2f dir = pointToGo - pos;

    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length > 1.f)
        dir /= length;

    _context.npc->move(dir * _context.npc->speed * dt);

    if (length < 3.f)
        _context.reachedPoint = true;
}

void PatrolState::Exit(NpcContext& _context)
{

}

void PatrolState::setPatrolPoints()
{
    float y = 200 + rand() % (900 - 200 + 1);
    float x = 400 + rand() % (1500 - 400 + 1);
    pointToGo = sf::Vector2f(x, y);
}