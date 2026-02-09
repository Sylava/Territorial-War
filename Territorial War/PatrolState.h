//#pragma once
//
//#include <iostream>
//#include <ostream>
//
//#include "NpcContext.h"
//#include "State.h"
//
//class PatrolState : public FSM::State<NpcContext>
//{
//public:
//    void Enter(NpcContext _context) override;
//    virtual void Execute(NpcContext _context) override;
//    void Exit(NpcContext _context) override;
//
//private:
//};

//#pragma once
//#include "StateMachine.h"
//#include "NpcContext.h"
//#include <SFML/Graphics.hpp>
//#include "State.h"
//
//class PatrolState : public FSM::State<NpcContext>
//{
//private:
//    sf::Vector2f target;
//    void chooseRandomTarget(NpcContext& ctx);
//public:
//    void Enter(NpcContext& ctx) override;
//    virtual void Update(NpcContext& ctx, float dt) override {}
//    void Exit(NpcContext& ctx) override;
//
//};
#pragma once
#include <iostream>
#include <ostream>
#include <SFML/Graphics.hpp>
#include "NpcContext.h"
#include "State.h"

class PatrolState : public FSM::State<NpcContext>
{
public:
    void Enter(NpcContext& context) override;
    virtual void Execute(NpcContext& context, const float dt) override;
    void Exit(NpcContext& context) override;

private:
    void setPatrolPoints(NpcContext& context);
    float getDistance(const sf::Vector2f& a, const sf::Vector2f& b);

    sf::Vector2f pointToGo;
};
