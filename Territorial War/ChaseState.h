//#pragma once
//#include <iostream>
//#include <ostream>
//
//#include "NpcContext.h"
//#include "State.h"
//
//namespace NpcAi
//{
//    class ChaseState : public FSM::State<NpcContext>
//    {
//        void Enter(NpcContext _context) override
//        {
//            std::cout << "Enter Patrol _State" << std::endl;
//        }
//
//        void Exit(NpcContext _context) override
//        {
//            std::cout << "Exit Patrol _State" << std::endl;
//        }
//    };
//}

#pragma once
#include "StateMachine.h"
#include "NpcContext.h"

class ChaseState : public State<NpcContext>
{
public:
    void Update(NpcContext& ctx, float dt) override;
};
