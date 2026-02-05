#pragma once
#include "StateMachine.h"
#include "ChaseState.h"
#include "Conditions.h"
#include "NpcContext.h"
#include "PatrolState.h"
#include "Entity.h"

using namespace NpcAi;

class Npc : public Entity<sf::RectangleShape>
{
public:
    Npc() : Entity(sf::RectangleShape({ 50.f, 50.f })){}
    ~Npc();
    FSM::StateMachine<NpcContext> fsm;

    NpcContext context{};
    sf::Vector2f PointA = { 600.f, 50.f };
    sf::Vector2f PointB = { 100.f, 600.f };
    sf::Vector2f direction;
    bool PointToGo = true;
    float speed = 100.f;

    void Init();

    void update(float dt) override;
};