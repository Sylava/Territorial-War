#include <random>
#include "PatrolState.h"
#include "../Entities/NPC.h"
#include "../GameCore/Map.h"

void PatrolState::Enter(NpcContext& context)
{
    context.reachedPoint = false;
    context.npc->isMoving = true;
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

}

// Donne un point où se diriger
void PatrolState::setPatrolPoints(NpcContext& context)
{
    float y = context.map->top + rand() % ((int)context.map->bottom - (int)context.map->top + 1);
    float x = context.map->left + rand() % ((int)context.map->right - (int)context.map->left + 1);
    pointToGo = sf::Vector2f(x, y);
}

// Retourne la distance entre deux points
float PatrolState::getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}