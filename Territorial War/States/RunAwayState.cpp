#include <random>
#include "RunAwayState.h"
#include "../Entities/NPC.h"
#include "../Entities/Player.h"

void RunAwayState::Enter(NpcContext& context)
{
    std::cout << "run away state" << std::endl;
    context.npc->runAwayTime = 0.f;
}

void RunAwayState::Execute(NpcContext& context, float dt)
{
    context.npc->runAwayTime += dt;
    context.npc->isMoving = true;
    sf::Vector2f dir = (context.player->position - context.npc->position).normalized();
    context.npc->move(-dir * context.npc->speed * dt, context.map);
}

void RunAwayState::Exit(NpcContext& context)
{

}