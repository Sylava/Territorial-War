#include "ChaseState.h"
#include "Npc.h"
#include "Player.h"
#include <cmath>

void ChaseState::Update(NpcContext& ctx, float dt)
{
    sf::Vector2f pos = ctx.npc->getPosition();
    sf::Vector2f target = ctx.player->getPosition();

    sf::Vector2f dir = target - pos;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (len > 1.f)
        dir /= len;

    ctx.npc->move(dir * ctx.npc->speed * dt);
}
