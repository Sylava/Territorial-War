#pragma once
#include "../FSM/StateMachine.h"
#include "../States/ChaseState.h"
#include "../FSM/NpcContext.h"
#include "../States/PatrolState.h"
#include "../States/IdleState.h"
#include "../States/HealState.h"
#include "../States/RunawayState.h"
#include "../Map.h"
#include "Entity.h"

using namespace NpcAi;

enum class Type
{
    Warrior,
    Healer,
};

class Npc : public Entity
{
public:
    Npc(sf::RenderWindow* inWindow);

    Type type;
    FSM::StateMachine<NpcContext> fsm;
    NpcContext context{};
    sf::CircleShape attackArea;
    Npc* target;
    float runAwayTime = 0.f;
    float skillCD = 1.f;
    float range;
    float detectionRadius;
    bool runForYourLife = false;

    virtual void Init(Map* map, Player* player, std::vector<Npc*>* npcs);
    void move(const sf::Vector2f& move, const Map* map);
    void moveOnAxis(float& pos, float& hitboxPos, float delta, float min, float max, const Map* map);
    void update(const float dt) override;

private:
};