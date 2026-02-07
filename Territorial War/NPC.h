#pragma once
#include "StateMachine.h"
#include "ChaseState.h"
#include "NpcContext.h"
#include "PatrolState.h"
#include "IdleState.h"
#include "Entity.h"

using namespace NpcAi;

class Npc
{
public:

    FSM::StateMachine<NpcContext> fsm;
    NpcContext context{};
    sf::Vector2f position;
    sf::Texture idleTex;
    sf::Texture runTex;
    std::optional<sf::Sprite> npcSprite;
    float speed = 180.f;
    bool isMoving = false;
    bool wasMoving = false;
    bool animMirror = false;

    void Init();
    void move(const sf::Vector2f& movement);
    void updateFsm(float dt);
};