#pragma once
#include <iostream>
#include <ostream>
#include <SFML/Graphics.hpp>
#include "../FSM/NpcContext.h"
#include "../FSM/State.h"

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
