#pragma once

class Npc;
class Player;
class Map;


class NpcContext
{
public:
    Npc* npc;
    Player* player;
    Map* map;
    bool reachedPoint = false;
    float idleTimer = 0.f;
    
    // Input
};
