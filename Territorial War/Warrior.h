#pragma once
#include "NPC.h"

class Warrior : public Npc
{
public:
	Warrior(sf::RenderWindow* inWindow, const Map* map);

    void update(const float dt);
    void draw();

private:
    sf::RenderWindow* window;
    int pv = 5;
    int idleIndex = 0;
    bool idleReverse = false;
    int runIndex = 0;
    bool runReverse = false;
    float animTime = 0.08f;
};

