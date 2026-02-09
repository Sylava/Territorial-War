#pragma once
#include "NPC.h"

class Warrior : public Npc
{
public:
	Warrior(sf::RenderWindow* inWindow, const Map* map);

    void update(const float dt);
    void idleAnimation(const float dt) override;
    void runAnimation(const float dt) override;
    void attackAnimation(const float dt) override;
    void draw();

private:
    sf::RenderWindow* window;
};

