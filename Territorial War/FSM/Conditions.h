#pragma once
#include "NpcContext.h"
#include "../Entities/NPC.h"
#include "../Entities/Player.h"

namespace NpcAi
{
    class Conditions
    {
    public:
        static bool hasReachedPoint(NpcContext& context)
        {
            return context.reachedPoint;
        }
        static bool hasWaited(NpcContext& context)
        {
            return context.idleTimer >= 2.f;
        }
        static bool isSeeingPlayer(NpcContext& context)
        {
            if (!context.npc || !context.player)
                return false;
            sf::Vector2f npcPos = context.npc->position;
            sf::Vector2f playerPos = context.player->position;
            sf::Vector2f diff = playerPos - npcPos;
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

            return dist < context.npc->detectionRadius;
        }
        static bool needHealing(NpcContext& context)
        {
            if (context.npc->skillCD >= 1.f)
            {
                for (Npc* npc : *context.npcs)
                {
                    if (npc->hp < npc->hpMax)
                    {
                        context.npc->target = npc;
                        return true;
                    }
                }
            }
            return false;
        }
        static bool onCooldown(NpcContext& context)
        {
            if (context.npc->skillCD <= 1.f)
                return true;
            return false;
        }
        static bool hasRunAway(NpcContext& context)
        {
            if (context.npc->runAwayTime >= 2.f)
                return true;
            return false;
        }
    };
}
