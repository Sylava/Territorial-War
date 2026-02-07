#pragma once

class Npc;
class Player;


class NpcContext
{
public:
    Npc* npc;
    Player* player;
    bool reachedPoint = false;
    float idleTimer = 0.f;
    // Input
    // Map
};
