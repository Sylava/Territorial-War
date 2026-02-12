#pragma once
#include "NPC.h"

class Warrior : public Npc
{
public:
	Warrior(sf::RenderWindow* inWindow, const Map* map);

    void Init(Map* map, Player* player, std::vector<Npc*>* npcs) override;
};

