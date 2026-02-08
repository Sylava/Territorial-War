#include "ChaseState.h"
#include "NPC.h"
#include "Player.h"
#include <random>

void ChaseState::Enter(NpcContext& context)
{
    std::cout << "Enter Chase State" << std::endl;
}

void ChaseState::Execute(NpcContext& context, float dt)
{
    float distance = getDistance(context.npc->position, context.player->position);
    if (distance <= context.npc->range)
    {
        context.npc->isMoving = false;
        if (context.npc->isAttacking == false)
        {
            context.npc->isAttacking = true;
            context.npc->attackIndex = 0;
            context.npc->attackAnimTime = 0.08f;
        }
    }
    else
    {
        context.npc->isMoving = true;
        sf::Vector2f dir = (context.player->position - context.npc->position).normalized();
        context.npc->move(dir * context.npc->speed * dt, context.map);
    }

}

void ChaseState::Exit(NpcContext& context)
{

}

float ChaseState::getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}