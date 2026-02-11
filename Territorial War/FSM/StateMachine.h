#pragma once
#include <vector>
#include "State.h"

namespace FSM
{
    template<typename ContextType>
    class StateMachine
    {
        using State = State<ContextType>;

    public:
        template<typename StateType>
        StateType* CreateState();

        void Init(State* _initialState, ContextType& context);
        void Update(ContextType& context, const float dt);

    private:
        std::vector<State*> states;

        State* currentState = nullptr;
    };
}

#include "StateMachine.inl"
