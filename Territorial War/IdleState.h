#pragma once
#pragma once
#include "StateMachine.h"
#include "NpcContext.h"

class IdleState : public State<NpcContext>
{
public:
    void Enter(NpcContext& ctx) override;
    void Update(NpcContext& ctx, float dt) override;

private:
    float timer = 0.f;
};
