//#pragma once
//
//class Npc;
//
//class NpcContext
//{
//public:
//    Npc* npc;
//    // Input
//    // Map
//};


#pragma once
class Npc;
class Player;

struct NpcContext
{
    Npc* npc = nullptr;
    Player* player = nullptr;
};
