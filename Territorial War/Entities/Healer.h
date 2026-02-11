#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "NPC.h"

class Healer : public Npc
{
public:
    Healer(sf::RenderWindow* inWindow, const Map* map);

    void update(const float dt);
    sf::Sprite* attackAnimation(const float dt) override;
    void healAnimation(const float dt);
    void Init(Map* map, Player* player, std::vector<Npc*>* npcs) override;
    void draw() override;

private:
    std::optional<sf::Sprite> healEffect;
    float healAnimTime = 0.8f;
    int healIndex = 0;
};

