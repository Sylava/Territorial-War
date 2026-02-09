#pragma once

#include <functional>

namespace FSM
{
    template<typename ContextType>
    class State
    {
        using Condition = std::function<bool(ContextType&)>;
        using _State = State<ContextType>;

    public:
        virtual ~State() = default;

        virtual void Enter(ContextType& context) {}
        virtual void Execute(ContextType& context, const float dt) {} // Update
        virtual void Exit(ContextType& context) {}

        void AddTransition(Condition _condition, _State* _newState);

        _State* TryGetNext(ContextType& context);

    private:
        std::vector<std::pair<Condition, _State*>> transitions;
    };
}

#include "State.inl"
