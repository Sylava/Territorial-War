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
#include <iostream>
#include <ostream>
#include <SFML/Graphics.hpp>
#include "NpcContext.h"
#include "State.h"

namespace NpcAi
{
    class ChaseState : public FSM::State<NpcContext>
    {
    private:
        void Enter(NpcContext& context) override;
        void Execute(NpcContext& context, const float dt);
        void Exit(NpcContext& context) override;

    public:
        float getDistance(const sf::Vector2f& a, const sf::Vector2f& b);
    };
}
