#pragma once
#include "../FSM/StateMachine.h"
#include "../States/ChaseState.h"
#include "../FSM/NpcContext.h"
#include "../States/PatrolState.h"
#include "../States/IdleState.h"
#include "../States/HealState.h"
#include "../States/RunawayState.h"
#include "../Map.h"
#include "Player.h"

using namespace NpcAi;

enum class Type
{
    Warrior,
    Healer,
};

class Npc
{
public:
    Type type;
    FSM::StateMachine<NpcContext> fsm;
    NpcContext context{};
    sf::Vector2f position;
    sf::CircleShape attackArea;
    sf::FloatRect hitbox;
    sf::Texture idleTex;
    sf::Texture runTex;
    sf::Texture attackTex;
    std::optional<sf::Sprite> npcSprite;
    Npc* target;
    float speed = 400.f;
    float invunerability = 0.6f;
    float runAwayTime = 0.f;
    float skillCD = 1.f;
    float range;
    float detectionRadius;
    bool isMoving = false;
    bool isAttacking = false;
    bool animMirror = false;
    bool idleReverse = false;
    bool runReverse = false;
    bool runForYourLife = false;
    int hp = 5;
    int hpMax = 5;
    int idleIndex = 0;
    int runIndex = 0;
    int attackIndex = 0;
    float attackAnimTime = 0.08f;
    float runAnimTime = 0.08f;
    float idleAnimTime = 0.08f;

    virtual void attackAnimation(const float dt) = 0;
    virtual void runAnimation(const float dt) = 0;
    virtual void idleAnimation(const float dt) = 0;
    virtual void Init(Map* map, Player* player, std::vector<Npc*>* npcs);
    void move(const sf::Vector2f& move, const Map* map);
    void moveOnAxis(float& pos, float& hitboxPos, float delta, float min, float max, const Map* map);
    virtual void update(float dt) = 0;
    virtual void draw() = 0;

private:
};