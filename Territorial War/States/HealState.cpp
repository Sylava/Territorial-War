#include "HealState.h"
#include "../Entities/NPC.h"
#include "../Entities/Player.h"

void HealState::Enter(NpcContext& context)
{

}

void HealState::Execute(NpcContext& context, float dt)
{
    if (getDistance(context.npc->position, context.npc->target->position) > context.npc->range)
    {
        sf::Vector2f dir = (context.npc->target->position - context.npc->position).normalized();
        context.npc->move(dir * context.npc->speed * dt, context.map);
    }
    else
    {
        context.npc->attack();
    }
}

void HealState::Exit(NpcContext& context)
{

}

float HealState::getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}
