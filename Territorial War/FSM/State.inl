#pragma once

template<typename ContextType>
void FSM::State<ContextType>::AddTransition(Condition _condition, _State* _newState)
{
    transitions.emplace_back(std::make_pair(_condition, _newState));
}

template<typename ContextType>
FSM::State<ContextType>::_State* FSM::State<ContextType>::TryGetNext(ContextType& context)
{
    for (auto& transition : transitions)
    {
        if (transition.first(context))
            return transition.second;
    }

    return nullptr;
}
