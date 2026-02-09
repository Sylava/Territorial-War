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

#include "StateMachine.h"
#include "ChaseState.h"
#include "NpcContext.h"
#include "IdleState.h"
#include "PatrolState.h"

#include "Map.h"
#include "Player.h"

using namespace NpcAi;

class Npc
{
public:


    FSM::StateMachine<NpcContext> fsm;
    NpcContext context{};
    sf::Vector2f position;
    sf::CircleShape attackArea;
    sf::FloatRect hitbox;
    sf::Texture idleTex;
    sf::Texture runTex;
    sf::Texture attackTex;
    std::optional<sf::Sprite> npcSprite;
    float speed = 400.f;
    float invunerability = 0.6f;
    float range;
    float detectionRadius;
    bool isMoving = false;
    bool isAttacking = false;
    bool animMirror = false;
    bool idleReverse = false;
    bool runReverse = false;
    int hp = 5;
    int idleIndex = 0;
    int runIndex = 0;
    int attackIndex = 0;
    float attackAnimTime = 0.08f;
    float runAnimTime = 0.08f;
    float idleAnimTime = 0.08f;

    virtual void attackAnimation(const float dt) = 0;
    virtual void runAnimation(const float dt) = 0;
    virtual void idleAnimation(const float dt) = 0;
    void Init(Map* map, Player* player);
    void move(const sf::Vector2f& move, const Map* map);
    void moveOnAxis(float& pos, float& hitboxPos, float delta, float min, float max, const Map* map);
    virtual void update(float dt) = 0;
    virtual void draw() = 0;

private:
};