#pragma once
#include <iostream>
#include <ostream>
#include <SFML/Graphics.hpp>
#include "NpcContext.h"
#include "State.h"

class IdleState : public FSM::State<NpcContext>
{
public:
    void Enter(NpcContext& _context) override;
    virtual void Execute(NpcContext& _context, float dt) override;
    void Exit(NpcContext& _context) override;

    float timer;
};

