#include "IdleState.h"
#include <random>

void IdleState::Enter(NpcContext& ctx)
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(1.f, 3.f);
    timer = dist(gen);
}

void IdleState::Update(NpcContext& ctx, float dt)
{
    timer -= dt;
}
