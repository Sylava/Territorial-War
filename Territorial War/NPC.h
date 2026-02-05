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

    void Init()
    {
        PatrolState* patrolState = fsm.CreateState<PatrolState>();
        ChaseState* chaseState = fsm.CreateState<ChaseState>();

        patrolState->AddTransition(Conditions::IsSeeingPlayer, chaseState);

        chaseState->AddTransition([](const NpcContext _context)
            {
                return !Conditions::IsSeeingPlayer(_context);
            }, patrolState);

        fsm.Init(patrolState, context);
    }

    sf::Vector2f getDirection(const sf::Vector2f& v)
    {
        float length = std::sqrt(v.x * v.x + v.y * v.y);
        return (length != 0.f) ? v / length : sf::Vector2f(0.f, 0.f);
    }

    void update(float dt) override
    {
        std::cout << "NPC update" << std::endl;
        fsm.Update(context);
        // calcul de la direction
        if (PointToGo)
        {
            direction = getDirection(PointA - getPosition());
        }
        else
        {
            direction = getDirection(PointB - getPosition());
        }
        move(direction * speed * dt);
        if (getPosition().x >= PointA.x)
            PointToGo = false;
        if (getPosition().y >= PointB.y)
            PointToGo = true;
    }
};

//#pragma once
//#include <SFML/Graphics.hpp>
//#include "StateMachine.h"
//#include "ChaseState.h"
//#include "Conditions.h"
//#include "NpcContext.h"
//#include "PatrolState.h"
//#include "Entity.h"
//
//using namespace NpcAi;
//
//class Npc : public Entity<sf::RectangleShape>
//{
//public:
//    Npc();
//    ~Npc() = default;
//
//    void Init();
//    void update(float dt, const sf::RenderWindow& window);
//
//    // Utilitaire
//    static sf::Vector2f Normalize(const sf::Vector2f& v);
//
//    // Données
//    FSM::StateMachine<NpcContext> fsm;
//    sf::Vector2f direction;
//    float speed = 100.f;
//};
