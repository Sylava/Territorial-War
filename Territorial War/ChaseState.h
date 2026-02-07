#pragma once
#include <iostream>
#include <ostream>

#include "NpcContext.h"
#include "State.h"

namespace NpcAi
{
    class ChaseState : public FSM::State<NpcContext>
    {
        void Enter(NpcContext& _context) override;
        void Execute(NpcContext& _context, float dt);
        void Exit(NpcContext& _context) override;
    };
}
