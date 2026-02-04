#pragma once

#include <iostream>
#include <ostream>

#include "NpcContext.h"
#include "State.h"

class PatrolState : public FSM::State<NpcContext>
{
public:
    void Enter(NpcContext _context) override;
    virtual void Execute(NpcContext _context) override;
    void Exit(NpcContext _context) override;

private:
};
