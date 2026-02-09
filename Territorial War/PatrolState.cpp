//#include "PatrolState.h"
//
//void PatrolState::Enter(NpcContext _context)
//{
//    std::cout << "Enter Patrol _State" << std::endl;
//}
//
//void PatrolState::Execute(NpcContext _context)
//{
//	std::cout << "Patrol State update" << std::endl;
//}
//
//void PatrolState::Exit(NpcContext _context)
//{
//    std::cout << "Exit Patrol _State" << std::endl;
//}

//#include "PatrolState.h"
//#include <random>
//#include <cmath>
//
//void PatrolState::Enter(NpcContext& ctx)
//{
//    chooseRandomTarget(ctx);
//}
//
//void PatrolState::chooseRandomTarget(NpcContext& ctx)
//{
//    static std::mt19937 gen(std::random_device{}());
//    std::uniform_int_distribution<int> distX(50, 750);
//    std::uniform_int_distribution<int> distY(50, 550);
//
//    target = sf::Vector2f(distX(gen), distY(gen));
//}
//
//void PatrolState::Update(NpcContext& ctx, float dt)
//{
//    sf::Vector2f pos = ctx.npc->getPosition();
//    sf::Vector2f dir = target - pos;
//
//    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//    if (len > 0.1f)
//        dir /= len;
//
//    ctx.npc->move(dir * ctx.npc->speed * dt);
//
//    if (std::abs(pos.x - target.x) < 5.f &&
//        std::abs(pos.y - target.y) < 5.f)
//    {
//        chooseRandomTarget(ctx);
//    }
//}
//
//void PatrolState::Exit(NpcContext& ctx)
//{
//    // Rien à faire pour l’instant
//}

#include "PatrolState.h"
#include "NPC.h"
#include "Map.h"
#include <random>
#include <cmath>

void PatrolState::Enter(NpcContext& context)
{
    std::cout << "Enter Patrol State" << std::endl;
    context.reachedPoint = false;
    context.npc->isMoving = true;
    context.reachedPoint = false;
    setPatrolPoints(context);
}

void PatrolState::Execute(NpcContext& context, const float dt)
{
    sf::Vector2f dir = (pointToGo - context.npc->position).normalized();
    context.npc->move(dir * context.npc->speed * dt, context.map);

    if (getDistance(pointToGo, context.npc->position) < 5.f || !context.npc->isMoving)
        context.reachedPoint = true;
}

void PatrolState::Exit(NpcContext& context)
{
    sf::Vector2f pos = ctx.npc->getPosition();
    sf::Vector2f dir = target - pos;

}

void PatrolState::setPatrolPoints(NpcContext& context)
{
    float y = context.map->top + rand() % ((int)context.map->bottom - (int)context.map->top + 1);
    float x = context.map->left + rand() % ((int)context.map->right - (int)context.map->left + 1);
    pointToGo = sf::Vector2f(x, y);
}

float PatrolState::getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}