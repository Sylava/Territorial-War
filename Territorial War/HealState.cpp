#include "HealState.h"
#include "NPC.h"
#include "Player.h"

void HealState::Enter(NpcContext& context)
{
    std::cout << "Enter Heal State" << std::endl;
}

void HealState::Execute(NpcContext& context, float dt)
{
    if (getDistance(context.npc->position, context.npc->target->position) > context.npc->range)
    {
        context.npc->isMoving = true;
        sf::Vector2f dir = (context.npc->target->position - context.npc->position).normalized();
        context.npc->move(dir * context.npc->speed * dt, context.map);
    }
    else
    {
        context.npc->isMoving = false;
        if(context.npc->isAttacking == false)
        {
            context.npc->isAttacking = true;
            if(context.npc->target->hp < context.npc->target->hpMax)
                context.npc->target->hp++;
            context.npc->attackIndex = 0;
            context.npc->attackAnimTime = 0.08f;
        }
        context.npc->attackAnimation(dt);
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
