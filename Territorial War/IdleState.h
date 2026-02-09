#pragma once
#include <iostream>
#include <ostream>
#include <SFML/Graphics.hpp>
#include "NpcContext.h"
#include "State.h"

class IdleState : public FSM::State<NpcContext>
{
public:
    void Enter(NpcContext& context) override;
    virtual void Execute(NpcContext& context, float dt) override;
    void Exit(NpcContext& context) override;

    float timer;
};

