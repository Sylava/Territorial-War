#include "NPC.h"
#include "../FSM/Conditions.h"

Npc::Npc()
{
    if (!hpBarTex.loadFromFile("assets/hpBar.png"))
        std::cout << "texture non chargee" << std::endl;
    if (!hpFillTex.loadFromFile("assets/hpBarFill.png"))
        std::cout << "texture non chargee" << std::endl;

}

void Npc::Init(Map* map, Player* player, std::vector<Npc*>* npcs)
{
    context.npc = this;
    context.npcs = npcs;
    context.map = map;
    context.player = player;
}

void Npc::move(const sf::Vector2f& move, const Map* map)
{
    if (move.x > 0.f)
        animMirror = true;
    else if (move.x < 0.f)
        animMirror = false;
    sf::Vector2f oldPosition = position;
    moveOnAxis(position.x, hitbox.position.x, move.x, map->left, map->right, map);
    moveOnAxis(position.y, hitbox.position.y, move.y, map->top, map->bottom, map);
    if (animMirror)
        attackArea.setPosition({ position.x + 25, position.y });
    else
        attackArea.setPosition({ position.x - 25, position.y });
    if (position == oldPosition)
        isMoving = false;
}

void Npc::hpBar()
{
    startBar->setPosition({ position.x - 14 - (hpMax / 2 * 64), position.y - 30});
    if (hpMax > 2)
    {
        for (int i = 0; i < hpMax - 2; ++i)
        {
            middleBar[i]->setPosition({ position.x - 64 * (hpMax - i), position.y - 30 });
        }
    }
    endBar->setPosition({ position.x + 14, position.y - 30 });
}

void Npc::moveOnAxis(float& pos, float& hitboxPos, float move, float min, float max, const Map* map)
{
    float oldPosition = pos;
    float oldHitbox = hitboxPos;

    pos += move;
    hitboxPos += move;
    if (hitboxPos > min && hitboxPos < max)
    {
        for (const sf::Sprite& rock : map->rocks)
        {
            if (hitbox.findIntersection(rock.getGlobalBounds()))
            {
                pos = oldPosition;
                hitboxPos = oldHitbox;
                break;
            }
        }
    }
    else
    {
        pos = oldPosition;
        hitboxPos = oldHitbox;
    }
}