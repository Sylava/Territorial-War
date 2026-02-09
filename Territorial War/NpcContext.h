#pragma once
#include <vector>

class Npc;
class Player;
class Map;


class NpcContext
{
public:
    Npc* npc;
    std::vector<Npc*>* npcs;
    Player* player;
    Map* map;
    bool reachedPoint = false;
    float idleTimer = 0.f;
};
