#pragma once

template<typename ContextType>
template<typename StateType>
StateType* FSM::StateMachine<ContextType>::CreateState()
{
    StateType* state = new StateType();
    states.push_back(state);

    return state;
}

template<typename ContextType>
void FSM::StateMachine<ContextType>::Init(State* _initialState, ContextType& context)
{
    currentState = _initialState;
    currentState->Enter(context);
}

template<typename ContextType>
void FSM::StateMachine<ContextType>::Update(ContextType& context, const float dt)
{
    currentState->Execute(context, dt);

    auto next = currentState->TryGetNext(context);

    if (next)
    {
        currentState->Exit(context);
        currentState = next;
        currentState->Enter(context);
    }
}
