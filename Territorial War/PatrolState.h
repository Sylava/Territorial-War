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
