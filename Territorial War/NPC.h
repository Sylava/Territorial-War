//#pragma once
//#include <SFML/Graphics.hpp>
//#include <random>
//#include "Entity.h"
//#include "Statemachine.h"
//#include "NpcContext.h"
//
//class Npc : public Entity<sf::RectangleShape>
//{
//public:
//    Npc();
//    ~Npc();
//
//    void Init();
//    void update(float dt) override;
//
//private:
//    sf::Vector2f getDirection(const sf::Vector2f& v);
//    void chooseRandomTarget();
//
//private:
//    FSM::StateMachine<NpcContext> fsm;
//    NpcContext context;
//
//    sf::Vector2f target;     // point aléatoire à atteindre
//    sf::Vector2f direction;  // direction normalisée
//    float speed = 100.f;
//
//    // Générateur aléatoire
//    std::mt19937 gen;
//    std::uniform_int_distribution<int> distX;
//    std::uniform_int_distribution<int> distY;
//};


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

#pragma once
#include "Entity.h"
#include "StateMachine.h"
#include "NpcContext.h"
#include "IdleState.h"
#include "PatrolState.h"
#include "ChaseState.h"
#include "Player.h"
class Npc : public Entity<sf::RectangleShape>
{
public:
    Npc();
    void Init(Player* player);
    void update(float dt) override;

    float speed = 120.f;

private:
    StateMachine<NpcContext> fsm;
    NpcContext context;
};
