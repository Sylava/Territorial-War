#pragma once
#include "StateMachine.h"
#include "ChaseState.h"
#include "NpcContext.h"
#include "PatrolState.h"
#include "IdleState.h"

using namespace NpcAi;

class Npc
{
public:

    FSM::StateMachine<NpcContext> fsm;
    NpcContext context{};
    sf::Vector2f position;
    sf::FloatRect hitbox;
    sf::Texture idleTex;
    sf::Texture runTex;
    std::optional<sf::Sprite> npcSprite;
    float speed = 730.f;
    bool isMoving = false;
    bool wasMoving = false;
    bool animMirror = false;
    float range;
    float detectionRadius;

    void Init();
    void move(const sf::Vector2f& move, const Map* map);
    void updateFsm(float dt);
};