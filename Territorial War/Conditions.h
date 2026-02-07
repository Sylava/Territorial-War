#pragma once
#include "NpcContext.h"
#include "NPC.h"
#include "Player.h"

namespace NpcAi
{
    class Conditions
    {
    public:
        static bool HasReachedPoint(NpcContext& context)
        {
            return context.reachedPoint;
        }

        static bool HasWaited(NpcContext& context)
        {
            return context.idleTimer >= 2.f;
        }
        static bool IsSeeingPlayer(NpcContext& context)
        {
            if (!context.npc || !context.player)
                return false;

            sf::Vector2f npcPos = context.npc->position;
            sf::Vector2f playerPos = context.player->position;

            sf::Vector2f diff = playerPos - npcPos;
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

            return dist < 200.f; // distance de détection (à ajuster)
        }
    };
}
