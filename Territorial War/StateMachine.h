//#pragma once
//
//#include <vector>
//
//#include "State.h"
//
//namespace FSM
//{
//    template<typename ContextType>
//    class StateMachine
//    {
//        using State = State<ContextType>;
//
//    public:
//        template<typename StateType>
//        StateType* CreateState();
//
//        void Init(State* _initialState, ContextType _context);
//        void Update(ContextType _context);
//
//    private:
//        std::vector<State*> states;
//
//        State* currentState = nullptr;
//    };
//}
//
//#include "StateMachine.inl"

#pragma once
#include <functional>
#include <vector>

template<typename Context>
class State
{
public:
    virtual ~State() = default;
    virtual void Enter(Context&) {}
    virtual void Update(Context&, float) {}
    virtual void Exit(Context&) {}

    void AddTransition(std::function<bool(const Context&)> condition, State* target) {
        transitions.push_back({ condition, target });
    }

    State* CheckTransitions(const Context& ctx) {
        for (auto& t : transitions)
            if (t.condition(ctx))
                return t.target;
        return nullptr;
    }

private:
    struct Transition {
        std::function<bool(const Context&)> condition;
        State* target;
    };

    std::vector<Transition> transitions;
};

template<typename Context>
class StateMachine
{
public:
    void Init(State<Context>* start, Context& ctx) {
        current = start;
        current->Enter(ctx);
    }

    void Update(Context& ctx, float dt) {
        if (!current) return;

        State<Context>* next = current->CheckTransitions(ctx);
        if (next && next != current) {
            current->Exit(ctx);
            current = next;
            current->Enter(ctx);
        }

        current->Update(ctx, dt);
    }

private:
    State<Context>* current = nullptr;
};

